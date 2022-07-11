#include "discord-ipc/serialization/party.h"
#include <nlohmann/json.hpp>

discord_ipc::types::party discord_ipc::types::party::from_json(std::string json) {
	nlohmann::json party_j = nlohmann::json::parse(json);
	party party;
	if (party_j.contains("id")) party.set_id(party_j["id"]);
	if (party_j.contains("size")) party.set_size(party_size::from_json(party_j["size"].get<nlohmann::json>().dump()));
	return party;
}
std::string discord_ipc::types::party::to_json() const {
	nlohmann::json party;
	if (this->id) party["id"] = *this->id;
	if (this->size) party["size"] = nlohmann::json::parse((*this->size).to_json());
	return party.dump();
}