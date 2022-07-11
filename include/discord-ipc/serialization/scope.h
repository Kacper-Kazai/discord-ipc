#pragma once
#include <string>

namespace discord_ipc::types {
	class scope {
		std::string value;
	public:
		scope(const char* value) {
			this->value = value;
		}
		std::string get() const {
			return this->value;
		};

		bool operator==(const scope& other) const {
			return this->value == other.value;
		}
		bool operator!=(const scope& other) const {
			return !operator==(other);
		}
	};
};