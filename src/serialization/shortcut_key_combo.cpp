#include "discord-ipc/serialization/shortcut_key_combo.h"
#include <nlohmann/json.hpp>

discord_ipc::types::shortcut_key_combo discord_ipc::types::shortcut_key_combo::from_json(std::string json) {
	nlohmann::json shorcut_key_combo_j = nlohmann::json::parse(json);
	return shortcut_key_combo(key_types(shorcut_key_combo_j["type"]), shorcut_key_combo_j["code"], shorcut_key_combo_j["name"]);
}
std::string discord_ipc::types::shortcut_key_combo::to_json() const {
	nlohmann::json shorcut_key_combo{
		{"type", this->type},
		{"code", this->code},
		{"name", this->name}
	};
	return shorcut_key_combo.dump();
}