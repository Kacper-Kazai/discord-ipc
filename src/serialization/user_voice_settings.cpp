#include "discord-ipc/serialization/user_voice_settings.h"
#include <nlohmann/json.hpp>

discord_ipc::types::user_voice_settings discord_ipc::types::user_voice_settings::from_json(std::string json) {
	nlohmann::json user_voice_settings_j = nlohmann::json::parse(json);
	std::string user_id = user_voice_settings_j["user_id"];
	user_voice_settings user_voice_settings(user_id);
	if (user_voice_settings_j.contains("pan")) {
		nlohmann::json pan = user_voice_settings_j["pan"];
		user_voice_settings.set_pan(pan::from_json(pan.dump()));
	}
	if (user_voice_settings_j.contains("volume")) user_voice_settings.set_volume(user_voice_settings_j["volume"]);
	if (user_voice_settings_j.contains("mute")) user_voice_settings.set_mute(user_voice_settings_j["mute"]);
	return user_voice_settings;
}
std::string discord_ipc::types::user_voice_settings::to_json() const {
	nlohmann::json user_voice_settings{
		{"user_id", this->user_id}
	};
	if (this->pan) user_voice_settings["pan"] = nlohmann::json::parse((*this->pan).to_json());
	if (this->volume) user_voice_settings["volume"] = *this->volume;
	if (this->mute) user_voice_settings["mute"] = *this->mute;
	return user_voice_settings.dump();
}