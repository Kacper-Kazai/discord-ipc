#include "discord-ipc/serialization/voice_settings_mode.h"
#include <nlohmann/json.hpp>

discord_ipc::types::voice_settings_mode discord_ipc::types::voice_settings_mode::from_json(std::string json) {
	nlohmann::json voice_settings_mode_j = nlohmann::json::parse(json);
	voice_settings_mode voice_settings_mode(
		voice_settings_mode_type(voice_settings_mode_j["type"].get<std::string>().c_str()),
		voice_settings_mode_j["auto_threshold"],
		voice_settings_mode_j["threshold"],
		shortcut_key_combo(
			key_types(voice_settings_mode_j["shortcut"]["type"]),
			voice_settings_mode_j["shortcut"]["code"],
			voice_settings_mode_j["shortcut"]["name"]
		),
		voice_settings_mode_j["delay"]
	);
	return voice_settings_mode;
}
std::string discord_ipc::types::voice_settings_mode::to_json() const {
	nlohmann::json voice_settings_mode{
		{"type", this->type.to_string()},
		{"auto_threshold", this->auto_threshold},
		{"threshold", this->threshold},
		{"shortcut", nlohmann::json::parse(this->shortcut.to_json())},
		{"delay", this->delay}
	};
	return voice_settings_mode.dump();
}