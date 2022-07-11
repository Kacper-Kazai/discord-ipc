#pragma once
#include <string>

namespace discord_ipc::types {
	class voice_settings_device {
		std::string id;
		std::string name;
	public:
		voice_settings_device() {};
		voice_settings_device(std::string id, std::string name) {
			this->id = id;
			this->name = name;
		}
		std::string get_id() const {
			return this->id;
		}
		std::string get_name() const {
			return this->name;
		}
		static voice_settings_device from_json(std::string json);
		std::string to_json() const;
		bool operator==(const voice_settings_device& other) const {
			return this->id == other.id && this->name == other.name;
		}
		bool operator!=(const voice_settings_device& other) const {
			return !(*this == other) ;
		}
	};
}