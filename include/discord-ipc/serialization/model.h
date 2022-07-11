#pragma once
#include <string>

namespace discord_ipc::types {
	class model {
		std::string name;
		std::string url;
	public:
		model() {};
		model(std::string name, std::string url) {
			this->name = name;
			this->url = url;
		}
		std::string get_name() const {
			return this->name;
		}
		std::string get_url() const {
			return this->url;
		}
		static model from_json(std::string);
		std::string to_json() const;
	};
}