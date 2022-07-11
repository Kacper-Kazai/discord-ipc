#pragma once
#include <string>

namespace discord_ipc::types {
	class button {
		std::string label;
		std::string url;
	public:
		button() {};
		button(std::string label, std::string url) {
			this->label = label;
			this->url = url;
		}
		std::string get_label() const {
			return this->label;
		}
		std::string get_url() const {
			return this->url;
		}
		static button from_json(std::string json);
		std::string to_json() const;

		bool operator==(const button& other) const {
			return this->label == other.label && this->url == other.url;
		}
		bool operator!=(const button& other) const {
			return !operator==(other);
		}
	};
}