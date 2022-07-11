#pragma once
#include "voice_settings_mode_type.h"
#include "shortcut_key_combo.h"
#include <string>

namespace discord_ipc::types {
	class voice_settings_mode {
		voice_settings_mode_type type;
		bool auto_threshold;
		float threshold;	
		shortcut_key_combo shortcut;
		float delay;
	public:
		voice_settings_mode() {};
		voice_settings_mode(voice_settings_mode_type type, bool auto_threshold, float threshold, shortcut_key_combo shortcut, float delay) {
			this->type = type;
			this->auto_threshold = auto_threshold;
			this->threshold = threshold;
			this->shortcut = shortcut;
			this->delay = delay;
		}
		voice_settings_mode_type get_type() const {
			return this->type;
		}
		bool get_auto_threshold() const {
			return this->auto_threshold;
		}
		float get_threshold() const {
			return this->threshold;
		}
		shortcut_key_combo get_shortcut_key_combo() const {
			return this->shortcut;
		}
		float get_delay() const {
			return this->delay;
		}
		static voice_settings_mode from_json(std::string json);
		std::string to_json() const;
	};
}