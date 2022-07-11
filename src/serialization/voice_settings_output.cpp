#include "discord-ipc/serialization/voice_settings_output.h"
#include <nlohmann/json.hpp>

discord_ipc::types::voice_settings_output discord_ipc::types::voice_settings_output::from_json(std::string json) {
	nlohmann::json voice_settings_output_j = nlohmann::json::parse(json);
	voice_settings_output voice_settings_output(voice_settings_output_j["device_id"], voice_settings_output_j["volume"]);
	for (auto device : voice_settings_output_j["available_devices"].get<nlohmann::json>()) {
		voice_settings_output.add_device(voice_settings_device::from_json(device.dump()));
	}
	return voice_settings_output;
}

std::string discord_ipc::types::voice_settings_output::to_json() const {
	nlohmann::json voice_settings_output{
		{"device_id", this->device_id},
		{"volume", this->volume}
	};
	nlohmann::json available_devices = nlohmann::json::array();
	for (auto device : this->available_device_array) {
		available_devices.push_back(nlohmann::json::parse(device.to_json()));
	}
	voice_settings_output["available_devices"] = available_devices;
	return voice_settings_output.dump();
}