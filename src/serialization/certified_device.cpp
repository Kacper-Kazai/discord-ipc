#include "discord-ipc/serialization/certified_device.h"
#include <nlohmann/json.hpp>

discord_ipc::types::certified_device discord_ipc::types::certified_device::from_json(std::string json) {
	nlohmann::json certified_device_j = nlohmann::json::parse(json);
	certified_device certified_device(
		certified_device_type((certified_device_j["type"].get<std::string>()).c_str()),
		certified_device_j["id"],
		vendor::from_json(certified_device_j["vendor"].get<nlohmann::json>().dump()),
		model::from_json(certified_device_j["model"].get<nlohmann::json>().dump()),
		certified_device_j["related"].get<std::vector<std::string>>()
	);
	if (certified_device_j.contains("echo_cancellation")) certified_device.set_echo_cancellation(certified_device_j["echo_cancellation"]);
	if(certified_device_j.contains("noise_suppression")) certified_device.set_noise_suppression(certified_device_j["noise_suppression"]);
	if(certified_device_j.contains("automatic_gain_control")) certified_device.set_automatic_gain_control(certified_device_j["automatic_gain_control"]);
	if(certified_device_j.contains("hardware_mute")) certified_device.set_hardware_mute(certified_device_j["hardware_mute"]);
	return certified_device;
}
std::string discord_ipc::types::certified_device::to_json() const {
	nlohmann::json cerified_device{
		{"type", this->type.get()},
		{"id", this->id},
		{"vendor", nlohmann::json::parse(this->vendor.to_json())},
		{"model", nlohmann::json::parse(this->model.to_json())},
		{"related", this->related_array}
	};
	if (this->echo_cancellation) cerified_device["echo_cancellation"] = *this->echo_cancellation;
	if (this->noise_suppression) cerified_device["noise_suppression"] = *this->noise_suppression;
	if (this->automatic_gain_control) cerified_device["automatic_gain_control"] = *this->automatic_gain_control;
	if (this->hardware_mute) cerified_device["hardware_mute"] = *this->hardware_mute;
	return cerified_device.dump();
}