#pragma once
#include <string>
#include <optional>
#include <vector>

namespace discord_ipc::types {
	class vendor {
		std::string name;
		std::string url;
	public:
		vendor() {}
		vendor(std::string name, std::string url) {
			this->name = name;
			this->url = url;
		}
		std::string get_name() const {
			return this->name;
		}
		std::string get_url() const {
			return this->url;
		}
		static vendor from_json(std::string json);
		std::string to_json() const;
	};
}