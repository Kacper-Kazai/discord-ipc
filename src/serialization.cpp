#include "discord-ipc/serialization.h"
#include <nlohmann/json.hpp>

using nlohmann::json;

std::string write_json_error(int code, std::string message) {
    json writer = {
        {"code", code},
        {"message", message}
    };

    return writer.dump();
}

void write_nonce_to_packet(packet& packet, std::string& nonce) {
    json data_json = json::parse(packet.data);
    
    data_json["nonce"] = nonce;

    packet.data = data_json.dump();
}

packet create_handshake_packet(int version, const char* application_id) {
    packet created_packet{};
    created_packet.opcode = opcode::handshake;
    json data_json{};
        
    data_json["v"] = version;
    data_json["client_id"] = application_id;

    created_packet.data = data_json.dump();

    return created_packet;
}

packet create_authorize_packet(const char* application_id, std::vector<std::string> scopes) {
    packet created_packet{};
    json data_json{};

    data_json["args"]["client_id"] = application_id;
    data_json["args"]["scopes"] = scopes;
    data_json["cmd"] = "AUTHORIZE";

    created_packet.data = data_json.dump();

    return created_packet;
}

packet create_authenticate_packet(std::string access_token) {
    packet created_packet{};
    json data_json{};

    data_json["args"]["access_token"] = access_token;
    data_json["cmd"] = "AUTHENTICATE";

    created_packet.data = data_json.dump();

    return created_packet;
}

packet create_subscribe_packet(const char* evt, std::string args) {
    packet created_packet{};
    json data_json{};

    data_json["evt"] = evt;
    if (!args.empty()) data_json["args"] = json::parse(args);
    data_json["cmd"] = "SUBSCRIBE";

    created_packet.data = data_json.dump();

    return created_packet;
}

packet create_command_packet(const char* evt, std::string args) {
    packet created_packet{};
    json data_json{};

    if (!args.empty()) data_json["args"] = json::parse(args);
    data_json["cmd"] = evt;

    created_packet.data = data_json.dump();

    return created_packet;
}