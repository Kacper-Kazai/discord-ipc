#pragma once
#include <string>

namespace discord_ipc::types {
	class party_size {
		int current_size{};
		int max_size{};
	public:
		party_size() {};
		party_size(int current_size, int max_size) {
			this->current_size = current_size;
			this->max_size = max_size;
		};
		int get_current_size() const {
			return this->current_size;
		}
		int get_max_size() const {
			return this->max_size;
		}
		static party_size from_json(std::string json);
		std::string to_json() const;
	};
}