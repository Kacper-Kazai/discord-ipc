#include "gtest/gtest.h"
#include "discord-ipc/serialization/certified_device_types.h"

using namespace discord_ipc::types;

TEST(serialization_certified_device_types, defaults_audioinput) {
	ASSERT_EQ(certified_device_type(certified_device_types::audio_input).get(), "audioinput");
}
TEST(serialization_certified_device_types, defaults_audiooutput) {
	ASSERT_EQ(certified_device_type(certified_device_types::audio_output).get(), "audiooutput");
}
TEST(serialization_certified_device_types, defaults_videoinput) {
	ASSERT_EQ(certified_device_type(certified_device_types::video_input).get(), "videoinput");
}