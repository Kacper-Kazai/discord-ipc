#include "gtest/gtest.h"
#include "discord-ipc/serialization/voice_settings_device.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_voice_settings_device, json_to_object) {
	voice_settings_device voice_settings_device = voice_settings_device::from_json("{\"id\":\"id\",\"name\":\"name\"}");
	ASSERT_EQ(voice_settings_device.get_id(), "id");
	ASSERT_EQ(voice_settings_device.get_name(), "name");
}

TEST(serialization_voice_settings_device, object_to_json) {
	voice_settings_device voice_settings_device("id", "name");
	ASSERT_EQ(voice_settings_device.to_json(), nlohmann::json::parse("{\"id\":\"id\",\"name\":\"name\"}").dump());
}