#include "discord-ipc/serialization/model.h"
#include <nlohmann/json.hpp>

discord_ipc::types::model discord_ipc::types::model::from_json(std::string json) {
	nlohmann::json model_j = nlohmann::json::parse(json);
	return model(model_j["name"], model_j["url"]);
}
std::string discord_ipc::types::model::to_json() const {
	nlohmann::json model{
		{"name", this->name},
		{"url", this->url}
	};

	return model.dump();
}