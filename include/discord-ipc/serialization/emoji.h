#pragma once
#include <string>
#include <optional>
#include <vector>

namespace discord_ipc::types {
	class emoji {
		std::string name;
		std::optional<std::string> id;
		std::optional<bool> animated;
	public:
		emoji(std::string name, std::optional<std::string> id=std::nullopt, std::optional<bool> animated=std::nullopt) {
			this->name = name;
			if (id) this->id = *id;
			if (animated) this->animated = *animated;
		}
		std::string get_name() const {
			return this->name;
		}
		std::optional<std::string> get_id() const {
			return this->id;
		}
		std::optional<bool> get_animated() const {
			return animated;
		}
		emoji& set_id(std::string id) {
			this->id = id;
			return *this;
		}
		emoji& set_animated(bool animated) {
			this->animated = animated;
			return *this;
		}
		static emoji from_json(std::string json);
		std::string to_json() const;
	};
}