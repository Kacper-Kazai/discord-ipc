#include "discord-ipc/serialization/voice_settings_input.h"
#include <nlohmann/json.hpp>

discord_ipc::types::voice_settings_input discord_ipc::types::voice_settings_input::from_json(std::string json) {
	nlohmann::json voice_settings_input_j = nlohmann::json::parse(json);
	voice_settings_input voice_settings_input(voice_settings_input_j["device_id"], voice_settings_input_j["volume"]);
	for (auto device : voice_settings_input_j["available_devices"].get<nlohmann::json>()) {
		voice_settings_input.add_device(voice_settings_device::from_json(device.dump()));
	}
	return voice_settings_input;
}

std::string discord_ipc::types::voice_settings_input::to_json() const {
	nlohmann::json voice_settings_input{
		{"device_id", this->device_id},
		{"volume", this->volume}
	};
	nlohmann::json available_devices = nlohmann::json::array();
	for (auto device : this->available_device_array) {
		available_devices.push_back(nlohmann::json::parse(device.to_json()));
	}
	voice_settings_input["available_devices"] = available_devices;
	return voice_settings_input.dump();
}