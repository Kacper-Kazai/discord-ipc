#pragma once
#include <string>
#include <optional>

namespace discord_ipc::types {
	class subscription {
		std::string evt;
		std::optional<std::string> args;
	public:
		subscription(std::string evt, std::optional<std::string> args = std::nullopt) {
			this->evt = evt;
			this->args = args;
		}
		const std::string get_evt() const {
			return this->evt;
		};
		const std::optional<std::string> args_to_json() const {
			return this->args;
		};
	};
};