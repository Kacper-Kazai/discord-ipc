#include "discord-ipc/ipc_connection.h"
#include "discord-ipc/serialization.h"
#include <nlohmann/json.hpp>

using discord_ipc::events;
using discord_ipc::packets;

static const int ipc_version = 1;
static ipc_connection instance;

ipc_connection* ipc_connection::create(const char* application_id) {
    instance.pipe = base_pipe::create();
    memcpy(instance.application_id, application_id, 64);
    instance.on(events::ready, [](std::string& event) {
        instance.state = state::connected;
    });
    return &instance;
}
void ipc_connection::destroy(ipc_connection*& connection) {
    connection->close();
    base_pipe::destroy(connection->pipe);
    connection = nullptr;
}

void ipc_connection::loop() {
    if (!is_open()) {
        open();
        return;
    }
    for (;;) {
        std::string read_message;

        if (!this->read(read_message)) break;

        nlohmann::json message = nlohmann::json::parse(read_message);

        std::string nonce{};
        if (message.contains("nonce") && !message.at("nonce").is_null())
            message.at("nonce").get_to(nonce);
        nlohmann::json data{};
        if (message.contains("data") && !message.at("data").is_null())
            message.at("data").get_to(data);

        if (!nonce.empty()) {
            this->response_emitter.emit(nonce, data.dump());
            this->response_emitter.remove(nonce);
            continue;
        }

        std::string event_name = "ERROR";
        if (message.contains("evt") && !message.at("evt").is_null())
            message.at("evt").get_to(event_name);

        this->emit(event_name, data.dump());
    }
}

void ipc_connection::open() {
    if (!this->pipe->is_open && !this->pipe->open()) return;

    packet send_packet = packets::handshake(ipc_version, application_id);

    if (!this->send(send_packet)) {
        close();
        return;
    }
    state = state::handshake;
}

void ipc_connection::close() {
    pipe->close();
    state = state::disconnected;
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

    if (!pipe->write(data_pointer, packet_size)) {
        close();
        return false;
    }
    return true;
}
bool ipc_connection::send(packet& send_packet, std::function<void(std::string&)> response) {
    auto nonce = this->response_emitter.on(response);

    write_nonce_to_packet(send_packet, nonce);

    return send(send_packet);
}

bool ipc_connection::read(std::string& message) {
    struct packet_header {
        opcode opcode;
        uint32_t length;
    };
    packet_header packet_header;

    for (;;) {
        bool did_read = pipe->read(&packet_header, sizeof(packet_header));
        if (!did_read) {
            if (!pipe->is_open) {
                auto error_data = write_json_error((int)error_code::pipe_closed, "Pipe closed");
                this->emit(events::error, error_data);
                close();
            }
            return false;
        }
        if (packet_header.length > 0) {
            char* buffer = (char*)malloc(sizeof(char) * packet_header.length);
            did_read = pipe->read(buffer, packet_header.length);
            if (!did_read) {
                auto error_data = write_json_error((int)error_code::read_corrupt, "Partial data in frame");
                this->emit(events::error, error_data);
                close();
                return false;
            }
            message = buffer;
            message[packet_header.length] = '\0';
        }

        switch (packet_header.opcode) {
        case opcode::close: {
            nlohmann::json data_json;

            if (!data_json.contains("data")) {
                close();
                return false;
            }
            nlohmann::json error_data_json;
            data_json.at("data").get_to(error_data_json);

            int error_code{};
            if (error_data_json.contains("code")) {
                error_data_json.at("code").get_to(error_code);
            }
            std::string error_message{};
            if (error_data_json.contains("message")) {
                error_data_json.at("message").get_to(error_message);
            }

            std::string error_data = write_json_error(error_code, error_message);
            this->emit(events::error, error_data);
            close();
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
            break;
        }
        case opcode::handshake:
        default:
            auto error_data = write_json_error((int)error_code::read_corrupt, "Bad ipc frame");
            this->emit(events::error, error_data);
            close();
            return false;
        }
    }
}