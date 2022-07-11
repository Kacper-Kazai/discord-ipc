#include "discord-ipc/serialization/vendor.h"
#include <nlohmann/json.hpp>

discord_ipc::types::vendor discord_ipc::types::vendor::from_json(std::string json) {
	nlohmann::json vendor_j = nlohmann::json::parse(json);
	return vendor(vendor_j["name"], vendor_j["url"]);
}
std::string discord_ipc::types::vendor::to_json() const {
	nlohmann::json vendor{
		{"name", this->name},
		{"url", this->url}
	};
	return vendor.dump();
}