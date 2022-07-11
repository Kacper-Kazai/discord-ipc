#pragma once
#include "voice_settings_mode_type.h"

namespace discord_ipc::types {
	struct voice_settings_mode_types {
		inline static const discord_ipc::types::voice_settings_mode_type pust_to_talk = "PUSH_TO_TALK";
		inline static const discord_ipc::types::voice_settings_mode_type voice_activity = "VOICE_ACTIVITY";
	};
}