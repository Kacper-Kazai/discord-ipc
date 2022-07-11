#pragma once
#include <string>

namespace discord_ipc::types {
	enum class key_types {
		KEYBOARD_KEY = 0,
		MOUSE_BUTTON = 1,
		KEYBOARD_MODIFIER_KEY = 2,
		GAMEPAD_BUTTON = 3
	};
}