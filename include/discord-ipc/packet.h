#pragma once
#include <cinttypes>
#include <string>

enum class opcode : uint32_t {
    handshake = 0,
    frame = 1,
    close = 2,
    ping = 3,
    pong = 4,
};

struct packet {
    opcode opcode{opcode::frame};
    std::string data;
};