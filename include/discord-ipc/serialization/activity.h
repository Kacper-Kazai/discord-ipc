#pragma once
#include "activity_types.h"
#include "timestamps.h"
#include "emoji.h"
#include "party.h"
#include "assets.h"
#include "secrets.h"
#include "activity_flags.h"
#include "button.h"
#include <string>
#include <optional>
#include <vector>

namespace discord_ipc::types {
	class activity {
		std::string name;
		discord_ipc::types::activity_types type;
		std::optional<std::string> url;
		int created_at;
		std::optional<discord_ipc::types::timestamps> timestamps;
		std::optional<std::string> application_id;
		std::optional<std::string> details;
		std::optional<std::string> state;
		std::optional<discord_ipc::types::emoji> emoji;
		std::optional<discord_ipc::types::party> party;
		std::optional<discord_ipc::types::assets> assets;
		std::optional<discord_ipc::types::secrets> secrets;
		std::optional<bool> instance;
		activity_flags flags{};
		std::vector<discord_ipc::types::button> button_array;
	public:
		activity() {};
		activity(std::string name, discord_ipc::types::activity_types type, int created_at) {
			this->name = name;
			this->type = type;
			this->created_at = created_at;
		}
		std::string get_name() const {
			return this->name;
		}
		discord_ipc::types::activity_types get_type() const {
			return this->type;
		}
		std::optional<std::string> get_url() const {
			return this->url;
		}
		int get_created_at() {
			return this->created_at;
		}
		std::optional<discord_ipc::types::timestamps> get_timestamps() const {
			return this->timestamps;
		};
		std::optional<std::string> get_application_id() const {
			return this->application_id;
		};
		std::optional<std::string> get_details() const {
			return this->details;
		};
		std::optional<std::string> get_state() const {
			return this->state;
		};
		std::optional<discord_ipc::types::emoji> get_emoji() const {
			return this->emoji;
		};
		std::optional<discord_ipc::types::party> get_party() const {
			return this->party;
		};
		std::optional<discord_ipc::types::assets> get_assets() const {
			return this->assets;
		};
		std::optional<discord_ipc::types::secrets> get_secrets() const {
			return this->secrets;
		};
		std::optional<bool> get_instance() const {
			return this->instance;
		};
		activity_flags get_flags() const {
			return this->flags;
		};
		std::vector<discord_ipc::types::button> get_buttons() const {
			return this->button_array;
		};
		activity& set_url(std::string url) {
			this->url = url;
			return *this;
		}
		activity& set_timestamps(discord_ipc::types::timestamps timestamps) {
			this->timestamps = timestamps;
			return *this;
		}
		activity& set_application_id(std::string application_id) {
			this->application_id = application_id;
			return *this;
		};
		activity& set_details(std::string details) {
			this->details = details;
			return *this;
		};
		activity& set_state(std::string state) {
			this->state = state;
			return *this;
		};
		activity& set_emoji(discord_ipc::types::emoji emoji) {
			this->emoji = emoji;
			return *this;
		};
		activity& set_party(discord_ipc::types::party party) {
			this->party = party;
			return *this;
		};
		activity& set_assets(discord_ipc::types::assets assets) {
			this->assets = assets;
			return *this;
		};
		activity& set_secrets(discord_ipc::types::secrets secrets) {
			this->secrets = secrets;
			return *this;
		};
		activity& set_instance(bool instance) {
			this->instance = instance;
			return *this;
		};
		activity& set_flags(int flags) {
			this->flags = activity_flags(flags);
			return *this;
		};
		activity& add_button(discord_ipc::types::button button) {
			this->button_array.push_back(button);
			return *this;
		}
		activity& remove_button(discord_ipc::types::button button) {
			auto button_item = std::find(this->button_array.begin(), this->button_array.end(), button);
			if (button_item != button_array.end()) button_array.erase(button_item);
			return *this;
		}
		static activity from_json(std::string);
		std::string to_json() const;
	};
}