#include <discord-ipc/serialization/activity.h>
#include <nlohmann/json.hpp>

discord_ipc::types::activity discord_ipc::types::activity::from_json(std::string json) {
	nlohmann::json activity_j = nlohmann::json::parse(json);
	activity activity(activity_j["name"], activity_j["type"], activity_j["created_at"]);
	if (activity_j.contains("url")) activity.set_url(activity_j["url"]);
	if (activity_j.contains("timestamps")) activity.set_timestamps(timestamps::from_json(activity_j["timestamps"].get<nlohmann::json>().dump()));
	if (activity_j.contains("application_id")) activity.set_application_id(activity_j["application_id"]);
	if (activity_j.contains("details")) activity.set_details(activity_j["details"]);
	if (activity_j.contains("state")) activity.set_state(activity_j["state"]);
	if (activity_j.contains("emoji")) activity.set_emoji(emoji::from_json(activity_j["emoji"].get<nlohmann::json>().dump()));
	if (activity_j.contains("party")) activity.set_party(party::from_json(activity_j["party"].get<nlohmann::json>().dump()));
	if (activity_j.contains("assets")) activity.set_assets(assets::from_json(activity_j["assets"].get<nlohmann::json>().dump()));
	if (activity_j.contains("secrets")) activity.set_secrets(secrets::from_json(activity_j["secrets"].get<nlohmann::json>().dump()));
	if (activity_j.contains("instance")) activity.set_instance(activity_j["instance"]);
	if (activity_j.contains("flags")) activity.set_flags(activity_j["flags"]);
	if (activity_j.contains("buttons")) {
		for (auto button : activity_j["buttons"].get<nlohmann::json>()) {
			activity.add_button(button::from_json(button.dump()));
		}
	}
	return activity;
}
std::string discord_ipc::types::activity::to_json() const {
	nlohmann::json activity{
		{"name", this->name},
		{"type", this->type},
		{"created_at", this->created_at}
	};
	if (this->url) activity["url"] = *this->url;
	if (this->timestamps) activity["timestamps"] = nlohmann::json::parse((*this->timestamps).to_json());
	if (this->application_id) activity["application_id"] = *this->application_id;
	if (this->details) activity["details"] = *this->details;
	if (this->state) activity["state"] = *this->state;
	if (this->emoji) activity["emoji"] = nlohmann::json::parse((*this->emoji).to_json());
	if (this->party) activity["party"] = nlohmann::json::parse((*this->party).to_json());
	if (this->assets) activity["assets"] = nlohmann::json::parse((*this->assets).to_json());
	if (this->secrets) activity["secrets"] = nlohmann::json::parse((*this->secrets).to_json());
	if (this->instance) activity["instance"] = *this->instance;
	if (this->flags.get() != 0) activity["flags"] = this->flags.get();
	if (!this->button_array.empty()) {
		nlohmann::json buttons = nlohmann::json::array();
		for (auto button : this->button_array) {
			buttons.push_back(nlohmann::json::parse(button.to_json()));
		}
		activity["buttons"] = buttons;
	}
	return activity.dump();
}