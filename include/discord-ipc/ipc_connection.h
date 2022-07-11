#pragma once
#include "discord-ipc/events_emitter.h"
#include "discord-ipc/base_pipe.h"
#include "discord-ipc/packet.h"

#include <thread>

class ipc_connection : public events_emitter<std::string>{
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

    std::string application_id;
    base_pipe* pipe;
    state state{ state::disconnected };

    std::thread thread;
    bool keep_running{ true };
    emitter_unique<std::string> response_emitter;

    inline bool is_open() const { return state != state::disconnected; }
    bool read(std::string&);
    void open();
    void close();
    void loop();
public:
    ipc_connection(std::string application_id);
    ~ipc_connection();

    std::string get_application_id() const {
        return this->application_id;
    }

    void start();
    void stop();
    void join();

    bool send(packet&);
    bool send(packet&, std::function<void(std::string&)>);
};