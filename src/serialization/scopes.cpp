#include "discord-ipc/serialization/scopes.h"
#include <nlohmann/json.hpp>

discord_ipc::types::scopes discord_ipc::types::scopes::from_json(std::string json) {
	std::vector<std::string> scope_array_j = nlohmann::json::parse(json);
	std::vector<scope> scope_array;
	for (auto scope_j : scope_array_j) {
		scope_array.push_back(scope(scope_j.c_str()));
	}
	return scopes(scope_array);
}
std::string discord_ipc::types::scopes::to_json() const {
	nlohmann::json scopes = nlohmann::json::array();
	for (auto scope : this->scope_array) {
		scopes.push_back(scope.get());
	}
	return scopes.dump();
}