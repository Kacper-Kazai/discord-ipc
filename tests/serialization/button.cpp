#include "gtest/gtest.h"
#include "discord-ipc/serialization/button.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_button, json_to_object) {
	button button = button::from_json("{\"label\":\"label\",\"url\":\"url\"}");
	ASSERT_EQ(button.get_label(), "label");
	ASSERT_EQ(button.get_url(), "url");
}

TEST(serialization_button, object_to_json) {
	button button("label", "url");
	ASSERT_EQ(button.to_json(), nlohmann::json::parse("{\"label\":\"label\",\"url\":\"url\"}").dump());
}