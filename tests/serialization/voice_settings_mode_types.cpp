#include "gtest/gtest.h"
#include "discord-ipc/serialization/voice_settings_mode_types.h"

using namespace discord_ipc::types;

TEST(serialization_voice_settings_mode_types, defaults_pust_to_talk) {
	ASSERT_EQ(voice_settings_mode_type(voice_settings_mode_types::pust_to_talk).to_string(), "PUSH_TO_TALK");
}
TEST(serialization_voice_settings_mode_types, defaults_voice_activity) {
	ASSERT_EQ(voice_settings_mode_type(voice_settings_mode_types::voice_activity).to_string(), "VOICE_ACTIVITY");
}