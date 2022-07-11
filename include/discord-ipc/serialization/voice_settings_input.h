#pragma once
#include "voice_settings_device.h"
#include <string>
#include <vector>

namespace discord_ipc::types {
	class voice_settings_input {
		std::string device_id;
		int volume;
		std::vector<voice_settings_device> available_device_array;
	public:
		voice_settings_input() {};
		voice_settings_input(std::string device_id, int volume) {
			this->device_id = device_id;
			this->volume = volume;
		}
		std::string get_device_id() const {
			return this->device_id;
		}
		int get_volume() const {
			return this->volume;
		} 
		std::vector<voice_settings_device> get_available_devices() const {
			return this->available_device_array;
		}
		voice_settings_input& add_device(voice_settings_device available_device) {
			available_device_array.push_back(available_device);
			return *this;
		}
		voice_settings_input& remove_device(voice_settings_device available_device) {
			auto device_item = std::find(this->available_device_array.begin(), this->available_device_array.end(), available_device);
			if (device_item != this->available_device_array.end()) this->available_device_array.erase(device_item);
			return *this;
		}
		static voice_settings_input from_json(std::string json);
		std::string to_json() const;
	};
}