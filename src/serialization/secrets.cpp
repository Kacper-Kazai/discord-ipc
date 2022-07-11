#include "discord-ipc/serialization/secrets.h"
#include <nlohmann/json.hpp>

discord_ipc::types::secrets discord_ipc::types::secrets::from_json(std::string json) {
	nlohmann::json secrets_j = nlohmann::json::parse(json);
	secrets secrets;
	if (secrets_j.contains("join")) secrets.set_join(secrets_j["join"]);
	if (secrets_j.contains("spectate")) secrets.set_spectate(secrets_j["spectate"]);
	if (secrets_j.contains("match")) secrets.set_match(secrets_j["match"]);
	return secrets;
}
std::string discord_ipc::types::secrets::to_json() const {
	nlohmann::json secrets;
	if (this->join) secrets["join"] = *this->join;
	if (this->spectate) secrets["spectate"] = *this->spectate;
	if (this->match) secrets["match"] = *this->match;
	return secrets.dump();
}