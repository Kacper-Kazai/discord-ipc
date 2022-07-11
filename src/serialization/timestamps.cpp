#include "discord-ipc/serialization/timestamps.h"
#include <nlohmann/json.hpp>

discord_ipc::types::timestamps discord_ipc::types::timestamps::from_json(std::string json) {
	nlohmann::json timestamps_j = nlohmann::json::parse(json);
	timestamps timestamps;
	if (timestamps_j.contains("start")) timestamps.set_start(timestamps_j["start"]);
	if (timestamps_j.contains("end")) timestamps.set_end(timestamps_j["end"]);
	return timestamps;
}
std::string discord_ipc::types::timestamps::to_json() const {
	nlohmann::json timestamps;
	if (this->start) timestamps["start"] = *this->start;
	if (this->end) timestamps["end"] = *this->end;
	return timestamps.dump();
}