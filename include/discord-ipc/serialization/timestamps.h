#pragma once
#include <string>
#include <optional>

namespace discord_ipc::types {
	class timestamps {
		std::optional<int> start;
		std::optional<int> end;
	public:
		timestamps(std::optional<int> start = std::nullopt, std::optional<int> end = std::nullopt) {
			if (start) this->start = *start;
			if (end) this->end = *end;
		};
		std::optional<int> get_start() const {
			return this->start;
		}
		std::optional<int> get_end() const {
			return this->end;
		}
		timestamps& set_start(int start) {
			this->start = start;
			return *this;
		}
		timestamps& set_end(int end) {
			this->end = end;
			return *this;
		}
		static timestamps from_json(std::string json);
		std::string to_json() const;
	};
}