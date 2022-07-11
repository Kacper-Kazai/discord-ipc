#pragma once
#include "party_size.h"
#include <string>
#include <optional>

namespace discord_ipc::types {
	class party {
		std::optional<int> id;
		std::optional<party_size> size;
	public:
		party(std::optional<int> id = std::nullopt, std::optional<party_size> size = std::nullopt) {
			if (id) this->id = *id;
			if (size) this->size = *size;
		};
		std::optional<int> get_id() const {
			return this->id;
		};
		std::optional<party_size> get_size() const {
			return this->size;
		};
		party& set_id(int id) {
			this->id = id;
			return *this;
		}
		party& set_size(party_size size) {
			this->size = size;
			return *this;
		}
		static party from_json(std::string json);
		std::string to_json() const;
	};
}