#pragma once
#include <string>

namespace discord_ipc::types {
	class activity_flag {
		int value;
	public:
		activity_flag(int value) {
			this->value = value;
		};
		int get() const {
			return this->value;
		};
	};
};