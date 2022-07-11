#pragma once
#include <string>

namespace discord_ipc::types {
	class voice_settings_mode_type {
		std::string value;
	public:
		voice_settings_mode_type() {};
		voice_settings_mode_type(const char* value) {
			this->value = value;
		};
		std::string to_string() const {
			return this->value;
		};
	};
}