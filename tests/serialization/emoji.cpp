#include "gtest/gtest.h"
#include "discord-ipc/serialization/emoji.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_emoji, json_to_object) {
	emoji emoji = emoji::from_json("{\"name\":\"name\",\"id\":\"id\",\"animated\":true}");
	ASSERT_EQ(emoji.get_name(), "name");
	ASSERT_TRUE(emoji.get_id());
	ASSERT_EQ(*emoji.get_id(), "id");
	ASSERT_TRUE(emoji.get_animated());
	ASSERT_EQ(*emoji.get_animated(), true);
}
TEST(serialization_emoji, json_to_object1) {
	emoji emoji = emoji::from_json("{\"name\":\"name\",\"id\":\"id\"}");
	ASSERT_EQ(emoji.get_name(), "name");
	ASSERT_TRUE(emoji.get_id());
	ASSERT_EQ(*emoji.get_id(), "id");
	ASSERT_FALSE(emoji.get_animated());
}
TEST(serialization_emoji, json_to_object2) {
	emoji emoji = emoji::from_json("{\"name\":\"name\",\"animated\":true}");
	ASSERT_EQ(emoji.get_name(), "name");
	ASSERT_FALSE(emoji.get_id());
	ASSERT_TRUE(emoji.get_animated());
	ASSERT_EQ(*emoji.get_animated(), true);
}
TEST(serialization_emoji, json_to_object3) {
	emoji emoji = emoji::from_json("{\"name\":\"name\"}");
	ASSERT_EQ(emoji.get_name(), "name");
	ASSERT_FALSE(emoji.get_id());
	ASSERT_FALSE(emoji.get_animated());
}

TEST(serialization_emoji, object_to_json) {
	emoji emoji("name", "id", true);
	ASSERT_EQ(emoji.to_json(), nlohmann::json::parse("{\"name\":\"name\",\"id\":\"id\",\"animated\":true}").dump());
}
TEST(serialization_emoji, object_to_json1) {
	emoji emoji("name", std::nullopt, true);
	emoji.set_animated(true);
	ASSERT_EQ(emoji.to_json(), nlohmann::json::parse("{\"name\":\"name\",\"animated\":true}").dump());
}
TEST(serialization_emoji, object_to_json2) {
	emoji emoji("name", "id");
	ASSERT_EQ(emoji.to_json(), nlohmann::json::parse("{\"name\":\"name\",\"id\":\"id\"}").dump());
}
TEST(serialization_emoji, object_to_json3) {
	emoji emoji("name");
	ASSERT_EQ(emoji.to_json(), nlohmann::json::parse("{\"name\":\"name\"}").dump());
}

TEST(serialization_emoji, func_set_id) {
	emoji emoji = emoji::from_json("{\"name\":\"name\",\"id\":\"id\",\"animated\":true}");
	emoji.set_id("edited");
	ASSERT_EQ(emoji.get_name(), "name");
	ASSERT_EQ(*emoji.get_id(), "edited");
	ASSERT_EQ(*emoji.get_animated(), true);
}
TEST(serialization_emoji, func_set_animated) {
	emoji emoji = emoji::from_json("{\"name\":\"name\",\"id\":\"id\",\"animated\":true}");
	emoji.set_animated(false);
	ASSERT_EQ(emoji.get_name(), "name");
	ASSERT_EQ(*emoji.get_id(), "id");
	ASSERT_EQ(*emoji.get_animated(), false);
}