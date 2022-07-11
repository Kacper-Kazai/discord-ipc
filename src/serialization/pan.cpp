#include "discord-ipc/serialization/pan.h"
#include <nlohmann/json.hpp>

discord_ipc::types::pan discord_ipc::types::pan::from_json(std::string json) {
	nlohmann::json pan_j = nlohmann::json::parse(json);
	return pan(pan_j["left"], pan_j["right"]);
}

std::string discord_ipc::types::pan::to_json() const {
	nlohmann::json pan{
		{"left", this->left},
		{"right", this->right}
	};
	return pan.dump();
}