#pragma once
#include "key_types.h"
#include <string>

namespace discord_ipc::types {
	class shortcut_key_combo {
		key_types type;
		int code;
		std::string name;
	public:
		shortcut_key_combo() {};
		shortcut_key_combo(key_types key_type, int code, std::string name) {
			this->type = key_type;
			this->code = code;
			this->name = name;
		};
		key_types get_type() const {
			return this->type;
		}
		int get_code() const {
			return this->code;
		}
		std::string get_name() const {
			return this->name;
		}
		static shortcut_key_combo from_json(std::string jso);
		std::string to_json() const;
	};
}