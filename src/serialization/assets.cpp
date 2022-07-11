#include "discord-ipc/serialization/assets.h"
#include <nlohmann/json.hpp>

discord_ipc::types::assets discord_ipc::types::assets::from_json(std::string json) {
	nlohmann::json assets_j = nlohmann::json::parse(json);
	assets assets;
	if (assets_j.contains("large_image")) assets.set_large_image(assets_j["large_image"]);
	if(assets_j.contains("large_text")) assets.set_large_text(assets_j["large_text"]);
	if(assets_j.contains("small_image")) assets.set_small_image(assets_j["small_image"]);
	if(assets_j.contains("small_text")) assets.set_small_text(assets_j["small_text"]);
	return assets;
}
std::string discord_ipc::types::assets::to_json() const {
	nlohmann::json assets;
	if (this->large_image) assets["large_image"] = *this->large_image;
	if (this->large_text) assets["large_text"] = *this->large_text;
	if (this->small_image) assets["small_image"] = *this->small_image;
	if (this->small_text) assets["small_text"] = *this->small_text;
	return assets.dump();
}