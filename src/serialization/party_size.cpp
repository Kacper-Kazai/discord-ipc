#include "discord-ipc/serialization/party_size.h"
#include <nlohmann/json.hpp>

discord_ipc::types::party_size discord_ipc::types::party_size::from_json(std::string json) {
	nlohmann::json party_size_j = nlohmann::json::parse(json);
	return party_size(party_size_j.at(0).get<int>(), party_size_j.at(1).get<int>());
}
std::string discord_ipc::types::party_size::to_json() const {
	nlohmann::json party_size = nlohmann::json::array();
	party_size.push_back(this->current_size);
	party_size.push_back(this->max_size);
	return party_size.dump();
}