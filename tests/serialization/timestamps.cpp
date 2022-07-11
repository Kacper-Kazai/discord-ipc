#include "gtest/gtest.h"
#include "discord-ipc/serialization/timestamps.h"
#include <vector>
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_timestamps, json_to_object) {
	timestamps timestamps = timestamps::from_json("{\"start\":1,\"end\":2}");
	ASSERT_TRUE(timestamps.get_start());
	ASSERT_EQ(*timestamps.get_start(), 1);
	ASSERT_TRUE(timestamps.get_end());
	ASSERT_EQ(*timestamps.get_end(), 2);
}
TEST(serialization_timestamps, json_to_object1) {
	timestamps timestamps = timestamps::from_json("{\"start\":1}");
	ASSERT_TRUE(timestamps.get_start());
	ASSERT_EQ(*timestamps.get_start(), 1);
	ASSERT_FALSE(timestamps.get_end());
}
TEST(serialization_timestamps, json_to_object2) {
	timestamps timestamps = timestamps::from_json("{\"end\":2}");
	ASSERT_FALSE(timestamps.get_start());
	ASSERT_TRUE(timestamps.get_end());
	ASSERT_EQ(*timestamps.get_end(), 2);
}

TEST(serialization_timestamps, object_to_json) {
	timestamps timestamps(1, 2);
	ASSERT_EQ(timestamps.to_json(), nlohmann::json::parse("{\"start\":1,\"end\":2}").dump());
}
TEST(serialization_timestamps, object_to_json1) {
	timestamps timestamps(1);
	ASSERT_EQ(timestamps.to_json(), nlohmann::json::parse("{\"start\":1}").dump());
}
TEST(serialization_timestamps, object_to_json2) {
	timestamps timestamps(std::nullopt, 2);
	ASSERT_EQ(timestamps.to_json(), nlohmann::json::parse("{\"end\":2}").dump());
}

TEST(serialization_timestamps, func_set_start) {
	timestamps timestamps(1, 2);
	timestamps.set_start(2);
	ASSERT_TRUE(timestamps.get_start());
	ASSERT_EQ(*timestamps.get_start(), 2);
}
TEST(serialization_timestamps, func_set_end) {
	timestamps timestamps(1, 2);
	timestamps.set_end(3);
	ASSERT_TRUE(timestamps.get_end());
	ASSERT_EQ(*timestamps.get_end(), 3);
}