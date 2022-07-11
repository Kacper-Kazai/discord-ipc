#include "gtest/gtest.h"
#include "discord-ipc/serialization/assets.h"
#include "nlohmann/json.hpp"

using namespace discord_ipc::types;

TEST(serialization_assets, json_to_object) {
	assets assets = assets::from_json("{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"}");
	ASSERT_TRUE(assets.get_large_image());
	ASSERT_EQ(*assets.get_large_image(), "large_image");
	ASSERT_TRUE(assets.get_large_text());
	ASSERT_EQ(*assets.get_large_text(), "large_text");
	ASSERT_TRUE(assets.get_small_image());
	ASSERT_EQ(*assets.get_small_image(), "small_image");
	ASSERT_TRUE(assets.get_small_text());
	ASSERT_EQ(*assets.get_small_text(), "small_text");
}
TEST(serialization_assets, json_to_object1) {
	assets assets = assets::from_json("{\"large_image\":\"large_image\"}");
	ASSERT_TRUE(assets.get_large_image());
	ASSERT_EQ(*assets.get_large_image(), "large_image");
	ASSERT_FALSE(assets.get_large_text());
	ASSERT_FALSE(assets.get_small_image());
	ASSERT_FALSE(assets.get_small_text());
}
TEST(serialization_assets, json_to_object2) {
	assets assets = assets::from_json("{\"large_text\":\"large_text\"}");
	ASSERT_FALSE(assets.get_large_image());
	ASSERT_TRUE(assets.get_large_text());
	ASSERT_EQ(*assets.get_large_text(), "large_text");
	ASSERT_FALSE(assets.get_small_image());
	ASSERT_FALSE(assets.get_small_text());
}

TEST(serialization_assets, object_to_json) {
	assets assets("large_image", "large_text", "small_image", "small_text");
	ASSERT_EQ(assets.to_json(), nlohmann::json::parse("{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"}").dump());
}
TEST(serialization_assets, object_to_json1) {
	assets assets("large_image");
	ASSERT_EQ(assets.to_json(), nlohmann::json::parse("{\"large_image\":\"large_image\"}").dump());
}
TEST(serialization_assets, object_to_json2) {
	assets assets(std::nullopt, "large_text");
	ASSERT_EQ(assets.to_json(), nlohmann::json::parse("{\"large_text\":\"large_text\"}").dump());
}

TEST(serialization_assets, func_set_large_image) {
	assets assets = assets::from_json("{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"}");
	assets.set_large_image("edited");
	ASSERT_EQ(*assets.get_large_image(), "edited");
	ASSERT_EQ(*assets.get_large_text(), "large_text");
	ASSERT_EQ(*assets.get_small_image(), "small_image");
	ASSERT_EQ(*assets.get_small_text(), "small_text");
}
TEST(serialization_assets, func_set_large_text) {
	assets assets = assets::from_json("{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"}");
	assets.set_large_text("edited");
	ASSERT_EQ(*assets.get_large_image(), "large_image");
	ASSERT_EQ(*assets.get_large_text(), "edited");
	ASSERT_EQ(*assets.get_small_image(), "small_image");
	ASSERT_EQ(*assets.get_small_text(), "small_text");
}
TEST(serialization_assets, func_set_small_image) {
	assets assets = assets::from_json("{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"}");
	assets.set_small_image("edited");
	ASSERT_EQ(*assets.get_large_image(), "large_image");
	ASSERT_EQ(*assets.get_large_text(), "large_text");
	ASSERT_EQ(*assets.get_small_image(), "edited");
	ASSERT_EQ(*assets.get_small_text(), "small_text");
}
TEST(serialization_assets, func_set_small_text) {
	assets assets = assets::from_json("{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"}");
	assets.set_small_text("edited");
	ASSERT_EQ(*assets.get_large_image(), "large_image");
	ASSERT_EQ(*assets.get_large_text(), "large_text");
	ASSERT_EQ(*assets.get_small_image(), "small_image");
	ASSERT_EQ(*assets.get_small_text(), "edited");
}
