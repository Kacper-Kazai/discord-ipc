#include "discord-ipc/events_emitter.h"
#include "uuid.h"

using uuids::uuid;

std::string generate_uuid() {
    uuid const id = uuids::uuid_system_generator{}();

    return uuids::to_string(id);
};