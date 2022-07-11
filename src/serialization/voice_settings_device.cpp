#include "discord-ipc/serialization/voice_settings_device.h"
#include <nlohmann/json.hpp>

discord_ipc::types::voice_settings_device discord_ipc::types::voice_settings_device::from_json(std::string json) {
	nlohmann::json voice_settings_device_j = nlohmann::json::parse(json);
	return voice_settings_device(voice_settings_device_j["id"], voice_settings_device_j["name"]);
}
std::string discord_ipc::types::voice_settings_device::to_json() const {
	nlohmann::json voice_settings_device{
		{"id", this->id},
		{"name", this->name}
	};
	return voice_settings_device.dump();
}