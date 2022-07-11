#pragma once
#include "discord-ipc/events_emitter.h"
#include "discord-ipc/base_pipe.h"
#include "discord-ipc/packet.h"

struct ipc_connection : events_emitter<std::string>{
    enum class state : uint32_t {
        disconnected,
        handshake,
        connected,
    };
     
    enum class error_code : int {
        success = 0,
        pipe_closed = 1,
        read_corrupt = 2,
    };

    char application_id[64]{};
    base_pipe* pipe{ nullptr };
    state state{ state::disconnected };
    emitter_unique<std::string> response_emitter;

    static ipc_connection* create(const char* application_id);
    static void destroy(ipc_connection*& connection);

    inline bool is_open() const { return state != state::disconnected; }

    void loop();
    void open();
    void close();
    bool send(packet&);
    bool send(packet&, std::function<void(std::string&)>);
    bool read(std::string&);
};
