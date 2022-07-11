#pragma once
#include "pan.h"
#include <string>
#include <optional>

namespace discord_ipc::types {
	class user_voice_settings {
		std::string user_id;
		std::optional<discord_ipc::types::pan> pan;
		std::optional<int> volume;
		std::optional<bool> mute;
	public:
		user_voice_settings() {};
		user_voice_settings(std::string user_id) {
			this->user_id = user_id;
		}
		std::string get_user_id() const {
			return this->user_id;
		}
		std::optional<discord_ipc::types::pan> get_pan() const {
			return this->pan;
		}
		std::optional<int> get_volume() const {
			return this->volume;
		}
		std::optional<bool> get_mute() const {
			return this->mute;
		}
		user_voice_settings& set_pan(discord_ipc::types::pan pan) {
			this->pan = pan;
			return *this;
		}
		user_voice_settings& set_volume(int volume) {
			this->volume = volume;
			return *this;
		}
		user_voice_settings& set_mute(bool mute) {
			this->mute = mute;
			return *this;
		}
		static user_voice_settings from_json(std::string);
		std::string to_json() const;
	};
}