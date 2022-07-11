#include "gtest/gtest.h"
#include "discord-ipc/serialization/shortcut_key_combo.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_shortcut_key_combo, json_to_object) {
	shortcut_key_combo shortcut_key_combo = shortcut_key_combo::from_json("{\"type\":0,\"code\":1,\"name\":\"name\"}");
	ASSERT_EQ(shortcut_key_combo.get_type(), key_types::KEYBOARD_KEY);
	ASSERT_EQ(shortcut_key_combo.get_code(), 1);
	ASSERT_EQ(shortcut_key_combo.get_name(), "name");
}

TEST(serialization_shortcut_key_combo, object_to_json) {
	shortcut_key_combo shortcut_key_combo(key_types::KEYBOARD_KEY, 1, "name");
	ASSERT_EQ(shortcut_key_combo.to_json(), nlohmann::json::parse("{\"type\":0,\"code\":1,\"name\":\"name\"}").dump());
}