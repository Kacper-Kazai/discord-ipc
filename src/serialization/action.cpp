#include "discord-ipc/serialization/action.h"
#include <nlohmann/json.hpp>

discord_ipc::types::action discord_ipc::types::action::from_json(std::string json) {
	nlohmann::json action_j = nlohmann::json::parse(json);
	return action(action_j["pid"], activity::from_json(action_j["activity"].get<nlohmann::json>().dump()));
}
std::string discord_ipc::types::action::to_json() const {
	nlohmann::json action{
		{"pid", this->pid},
		{"activity", nlohmann::json::parse(this->activity.to_json())}
	};
	return action.dump();
}