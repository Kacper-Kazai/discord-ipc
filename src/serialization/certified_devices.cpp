#include "discord-ipc/serialization/certified_devices.h"
#include "discord-ipc/serialization/certified_device.h"
#include <nlohmann/json.hpp>

discord_ipc::types::certified_devices discord_ipc::types::certified_devices::from_json(std::string json) {
	nlohmann::json certified_devices_j = nlohmann::json::parse(json);
	certified_devices certified_devices;
	for (auto certified_device : certified_devices_j["buttons"].get<nlohmann::json>()) {
		certified_devices.add(certified_device::from_json(certified_device.dump()));
	}
	return certified_devices;
}
std::string discord_ipc::types::certified_devices::to_json() const {
	nlohmann::json devices = nlohmann::json::array();
	for (auto certified_device : this->devices) {
		devices.push_back(nlohmann::json::parse(certified_device.to_json()));
	}
	nlohmann::json certified_devices{
		{"buttons", devices}
	};
	return certified_devices.dump();
}