#include "discord-ipc/serialization/button.h"
#include <nlohmann/json.hpp>

discord_ipc::types::button discord_ipc::types::button::from_json(std::string json) {
	nlohmann::json button_j = nlohmann::json::parse(json);
	return button(button_j["label"], button_j["url"]);
}
std::string discord_ipc::types::button::to_json() const {
	nlohmann::json button{
		{"label", this->label},
		{"url", this->url}
	};
	return button.dump();
}