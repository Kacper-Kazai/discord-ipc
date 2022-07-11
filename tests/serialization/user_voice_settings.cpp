#include "gtest/gtest.h"
#include "discord-ipc/serialization/user_voice_settings.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_user_voice_settings, json_to_object) {
	user_voice_settings user_voice_settings = user_voice_settings::from_json("{\"user_id\":\"user_id\",\"pan\":{\"left\":1.0,\"right\":1.0},\"volume\":100,\"mute\":true}");
	ASSERT_EQ(user_voice_settings.get_user_id(), "user_id");
	ASSERT_TRUE(user_voice_settings.get_pan());
	ASSERT_EQ((*user_voice_settings.get_pan()).get_left(), 1);
	ASSERT_EQ((*user_voice_settings.get_pan()).get_right(), 1);
	ASSERT_TRUE(user_voice_settings.get_volume());
	ASSERT_EQ((*user_voice_settings.get_volume()), 100);
	ASSERT_TRUE(user_voice_settings.get_mute());
	ASSERT_EQ((*user_voice_settings.get_mute()), true);
}
TEST(serialization_user_voice_settings, json_to_object1) {
	user_voice_settings user_voice_settings = user_voice_settings::from_json("{\"user_id\":\"user_id\",\"pan\":{\"left\":1.0,\"right\":1.0}}");
	ASSERT_EQ(user_voice_settings.get_user_id(), "user_id");
	ASSERT_TRUE(user_voice_settings.get_pan());
	ASSERT_EQ((*user_voice_settings.get_pan()).get_left(), 1);
	ASSERT_EQ((*user_voice_settings.get_pan()).get_right(), 1);
	ASSERT_FALSE(user_voice_settings.get_volume());
	ASSERT_FALSE(user_voice_settings.get_mute());
}
TEST(serialization_user_voice_settings, json_to_object2) {
	user_voice_settings user_voice_settings = user_voice_settings::from_json("{\"user_id\":\"user_id\",\"volume\":100}");
	ASSERT_EQ(user_voice_settings.get_user_id(), "user_id");
	ASSERT_FALSE(user_voice_settings.get_pan());
	ASSERT_TRUE(user_voice_settings.get_volume());
	ASSERT_EQ((*user_voice_settings.get_volume()), 100);
	ASSERT_FALSE(user_voice_settings.get_mute());
}

TEST(serialization_user_voice_settings, object_to_json) {
	user_voice_settings user_voice_settings("user_id");
	user_voice_settings
		.set_pan(pan(1, 1))
		.set_volume(100)
		.set_mute(true);
	ASSERT_EQ(user_voice_settings.to_json(), nlohmann::json::parse("{\"user_id\":\"user_id\",\"pan\":{\"left\":1.0,\"right\":1.0},\"volume\":100,\"mute\":true}").dump());
}
TEST(serialization_user_voice_settings, object_to_json1) {
	user_voice_settings user_voice_settings("user_id");
	user_voice_settings.set_pan(pan(1, 1));
	ASSERT_EQ(user_voice_settings.to_json(), nlohmann::json::parse("{\"user_id\":\"user_id\",\"pan\":{\"left\":1.0,\"right\":1.0}}").dump());
}
TEST(serialization_user_voice_settings, object_to_json2) {
	user_voice_settings user_voice_settings("user_id");
	user_voice_settings.set_volume(100);
	ASSERT_EQ(user_voice_settings.to_json(), nlohmann::json::parse("{\"user_id\":\"user_id\",\"volume\":100}").dump());
}

TEST(serialization_user_voice_settings, func_set_pan) {
	user_voice_settings user_voice_settings = user_voice_settings::from_json("{\"user_id\":\"user_id\",\"pan\":{\"left\":1.0,\"right\":1.0},\"volume\":100,\"mute\":true}");
	user_voice_settings.set_pan(pan(0.5, 0.5));
	ASSERT_EQ((*user_voice_settings.get_pan()).get_right(), 0.5);
	ASSERT_EQ((*user_voice_settings.get_pan()).get_left(), 0.5);
}
TEST(serialization_user_voice_settings, func_set_volume) {
	user_voice_settings user_voice_settings = user_voice_settings::from_json("{\"user_id\":\"user_id\",\"pan\":{\"left\":1.0,\"right\":1.0},\"volume\":100,\"mute\":true}");
	user_voice_settings.set_volume(50);
	ASSERT_EQ((*user_voice_settings.get_volume()), 50);
}
TEST(serialization_user_voice_settings, func_set_mute) {
	user_voice_settings user_voice_settings = user_voice_settings::from_json("{\"user_id\":\"user_id\",\"pan\":{\"left\":1.0,\"right\":1.0},\"volume\":100,\"mute\":true}");
	user_voice_settings.set_mute(false);
	ASSERT_EQ((*user_voice_settings.get_mute()), false);
}