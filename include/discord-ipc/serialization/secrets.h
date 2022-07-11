#pragma once
#include <string>
#include <optional>

namespace discord_ipc::types {
	class secrets {
		std::optional<std::string> join;
		std::optional<std::string> spectate;
		std::optional<std::string> match;
	public:
		secrets(std::optional<std::string> join = std::nullopt, std::optional<std::string> spectate = std::nullopt, std::optional<std::string> match = std::nullopt) {
			if (join) this->join = *join;
			if (spectate) this->spectate = *spectate;
			if (match) this->match = *match;
		};
		std::optional<std::string> get_join() const {
			return this->join;
		};
		std::optional<std::string> get_spectate() const {
			return this->spectate;
		};
		std::optional<std::string> get_match() const {
			return this->match;
		};
		secrets& set_join(std::string join) {
			this->join = join;
			return *this;
		}
		secrets& set_spectate(std::string spectate) {
			this->spectate = spectate;
			return *this;
		}
		secrets& set_match(std::string match) {
			this->match = match;
			return *this;
		}
		static secrets from_json(std::string json);
		std::string to_json() const;
	};
}