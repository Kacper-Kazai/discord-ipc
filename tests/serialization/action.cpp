#include "gtest/gtest.h"
#include "discord-ipc/serialization/action.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;


TEST(serialization_action, json_to_object) {
	action action = action::from_json("{\"pid\":1,\"activity\":{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}}");
	ASSERT_EQ(action.get_pid(), 1);
}

TEST(serialization_action, object_to_json) {
	activity activity("name", activity_types::streaming, 1);
	activity
		.set_url("url")
		.set_timestamps(timestamps(1, 2))
		.set_application_id("application_id")
		.set_details("details")
		.set_state("state")
		.set_emoji(emoji("name", "id", true))
		.set_party(party(1, party_size(1, 2)))
		.set_assets(assets("large_image", "large_text", "small_image", "small_text"))
		.set_secrets(secrets("join", "spectate", "match"))
		.set_instance(true)
		.set_flags(1)
		.add_button(button("label", "url"));
	action action(1, activity);
	ASSERT_EQ(action.to_json(), nlohmann::json::parse("{\"pid\":1,\"activity\":{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}}").dump());
}