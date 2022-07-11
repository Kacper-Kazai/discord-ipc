#pragma once
#include "certified_device.h"
#include <vector>
#include <string>

namespace discord_ipc::types {
	class certified_devices {
		std::vector<certified_device> devices;
	public:
		certified_devices() {};
		certified_devices(std::vector<certified_device> devices) {
			this->devices = devices;
		};
		std::vector<certified_device> get_devices() const {
			return this->devices;
		}
		certified_devices& add(certified_device certified_device) {
			devices.push_back(certified_device);
			return *this;
		}
		certified_devices& remove(certified_device certified_device) {
			auto device_item = std::find(this->devices.begin(), this->devices.end(), certified_device);
			if (device_item != devices.end()) devices.erase(device_item);
			return *this;
		}
		static certified_devices from_json(std::string json);
		std::string to_json() const;
	};
}