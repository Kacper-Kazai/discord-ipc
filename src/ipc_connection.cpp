#include "discord-ipc/ipc_connection.h"
#include "discord-ipc/serialization.h"
#include <nlohmann/json.hpp>

static const int ipc_version = 1;

using discord_ipc::events;
using discord_ipc::commands;
using discord_ipc::packets;

ipc_connection::ipc_connection(std::string application_id) {
    this->pipe = new base_pipe();
    this->application_id = application_id;
}
ipc_connection::~ipc_connection() {
    this->close();
    delete this->pipe;
}

void ipc_connection::start() {
    this->thread = std::thread([&]() {
        while (this->keep_running) {
            this->loop();
        }
    });
}
void ipc_connection::stop() {
    this->keep_running = false;
}
void ipc_connection::join() {
    if (this->thread.joinable()) {
        this->thread.join();
    }
}

void ipc_connection::open() {
    if (!this->pipe->is_open && !this->pipe->open()) return;

    packet handshake_packet = packets::handshake(ipc_version, application_id);
    if (!this->send(handshake_packet)) {
        this->close();
        return;
    }

    this->on(events::ready, [&](std::string& event) {
        this->state = state::connected;
    });
    this->state = state::handshake;
}
void ipc_connection::close() {
    this->pipe->close();
    this->state = state::disconnected;
}

void ipc_connection::loop() {
    if (!this->is_open()) {
        this->open();
        return;
    }
    for (;;) {
        std::string read_message;
        if (!this->read(read_message)) break;

        nlohmann::json packet = nlohmann::json::parse(read_message);

        std::string cmd = packet["cmd"];
        if (cmd != commands::dispatch) {
            std::string nonce = packet["nonce"];
            this->response_emitter.emit(nonce, packet.dump());
            this->response_emitter.remove(nonce);
        } else {
            std::string evt = packet["evt"];
            this->emit(evt, packet.dump());
        }
    }
}

bool ipc_connection::send(packet& packet) {
    uint32_t length = packet.data.length();
    size_t packet_size = sizeof(opcode) + sizeof(uint32_t) + sizeof(char) * length;

    uint8_t* data = (uint8_t*)malloc(packet_size);
    uint8_t* data_pointer = data;

    memcpy(data, &packet, sizeof(opcode));
    data += sizeof(opcode);

    memcpy(data, &length, sizeof(uint32_t));
    data += sizeof(uint32_t);

    memcpy(data, packet.data.c_str(), sizeof(char) * length);

    if (!this->pipe->write(data_pointer, packet_size)) {
        close();
        return false;
    }
    return true;
}
bool ipc_connection::send(packet& send_packet, std::function<void(std::string&)> response) {
    std::string nonce = this->response_emitter.on(response);

    write_nonce_to_packet(send_packet, nonce);

    return this->send(send_packet);
}


bool ipc_connection::read(std::string& message) {
    struct packet_header {
        opcode opcode;
        uint32_t length;
    };
    packet_header packet_header;

    for (;;) {
        bool did_read = this->pipe->read(&packet_header, sizeof(packet_header));
        if (!did_read) {
            if (!this->pipe->is_open) {
                std::string error_data = write_json_error((int)error_code::pipe_closed, "Pipe closed");
                this->emit(events::error, error_data);
                close();
            }
            return false;
        }
        if (packet_header.length > 0) {
            char* buffer = (char*)malloc(sizeof(char) * packet_header.length);
            did_read = this->pipe->read(buffer, packet_header.length);
            if (!did_read) {
                std::string error_data = write_json_error((int)error_code::read_corrupt, "Partial data in frame");
                this->emit(events::error, error_data);
                this->close();
                return false;
            }
            message = buffer;
            message[packet_header.length] = '\0';
        }

        switch (packet_header.opcode) {
        case opcode::close: {
            nlohmann::json packet_json = nlohmann::json::parse(message);

            if (!packet_json.contains("code")) {
                this->close();
                return false;
            }
            int error_code = packet_json["code"];

            std::string error_message{};
            if (packet_json.contains("message")) {
                error_message = packet_json["message"];
            }

            std::string error_data = write_json_error(error_code, error_message);
            this->emit(events::error, error_data);
            this->close();
            return false;
        }
        case opcode::frame: {
            return true;
        }
        case opcode::ping: {
            packet pong_packet;
            pong_packet.opcode = opcode::pong;
            pong_packet.data = message;
            if (!this->send(pong_packet)) {
                close();
            }
            break;
        }
        case opcode::pong: {
            printf("pong\n");
            break;
        }
        case opcode::handshake:
        default:
            std::string error_data = write_json_error((int)error_code::read_corrupt, "Bad ipc frame");
            this->emit(events::error, error_data);
            this->close();
            return false;
        }
    }
}