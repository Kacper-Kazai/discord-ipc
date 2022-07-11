#include "discord-ipc/serialization/emoji.h"
#include <nlohmann/json.hpp>

discord_ipc::types::emoji discord_ipc::types::emoji::from_json(std::string json) {
	nlohmann::json emoji_j = nlohmann::json::parse(json);
	emoji emoji(emoji_j["name"]);
	if (emoji_j.contains("id")) emoji.set_id(emoji_j["id"]);
	if (emoji_j.contains("animated")) emoji.set_animated(emoji_j["animated"]);
	return emoji;
}
std::string discord_ipc::types::emoji::to_json() const {
	nlohmann::json emoji{
		{"name", this->name}
	};
	if(this->id) emoji["id"] = *this->id;
	if(this->animated) emoji["animated"] = *this->animated;
	return emoji.dump();
}