#pragma once
#include "discord-ipc/packet.h"
#include <vector>

std::string write_json_error(int code, std::string message);
void write_nonce_to_packet(packet& packet, std::string& nonce);

packet create_handshake_packet(int version, const char* application_id);
packet create_authorize_packet(const char* application_id, std::vector<std::string> scopes);
packet create_authenticate_packet(std::string access_token);
packet create_subscribe_packet(const char* evt, std::string args);
packet create_command_packet(const char* evt, std::string args);

