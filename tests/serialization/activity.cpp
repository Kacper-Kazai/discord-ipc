#include "gtest/gtest.h"
#include "discord-ipc/serialization/activity.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_activity, json_to_object) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	std::vector<discord_ipc::types::button> buttons{button("label", "url")};
	ASSERT_EQ(activity.get_name(), "name");
	ASSERT_EQ(activity.get_type(), activity_types::streaming);
	ASSERT_TRUE(activity.get_url());
	ASSERT_EQ(*activity.get_url(), "url");
	ASSERT_EQ(activity.get_created_at(), 1);
	ASSERT_TRUE(activity.get_timestamps());
	ASSERT_EQ((*activity.get_timestamps()).get_start(), 1);
	ASSERT_EQ((*activity.get_timestamps()).get_end(), 2);
	ASSERT_TRUE(activity.get_application_id());
	ASSERT_EQ(*activity.get_application_id(), "application_id");
	ASSERT_TRUE(activity.get_details());
	ASSERT_EQ(*activity.get_details(), "details");
	ASSERT_TRUE(activity.get_state());
	ASSERT_EQ(*activity.get_state(), "state");
	ASSERT_TRUE(activity.get_emoji());
	ASSERT_EQ((*activity.get_emoji()).get_name(), "name");
	ASSERT_EQ((*activity.get_emoji()).get_id(), "id");
	ASSERT_EQ((*activity.get_emoji()).get_animated(), true);
	ASSERT_TRUE(activity.get_party());
	ASSERT_TRUE((*activity.get_party()).get_id());
	ASSERT_EQ((*(*activity.get_party()).get_id()), 1);
	ASSERT_TRUE((*activity.get_party()).get_size());
	ASSERT_EQ((*(*activity.get_party()).get_size()).get_current_size(), 1);
	ASSERT_EQ((*(*activity.get_party()).get_size()).get_max_size(), 2);
	ASSERT_TRUE(activity.get_assets());
	ASSERT_TRUE((*activity.get_assets()).get_large_image());
	ASSERT_EQ(*(*activity.get_assets()).get_large_image(), "large_image");
	ASSERT_TRUE((*activity.get_assets()).get_large_text());
	ASSERT_EQ(*(*activity.get_assets()).get_large_text(), "large_text");
	ASSERT_TRUE((*activity.get_assets()).get_small_image());
	ASSERT_EQ(*(*activity.get_assets()).get_small_image(), "small_image");
	ASSERT_TRUE((*activity.get_assets()).get_small_text());
	ASSERT_EQ(*(*activity.get_assets()).get_small_text(), "small_text");
	ASSERT_TRUE(activity.get_secrets());
	ASSERT_TRUE((*activity.get_secrets()).get_join());
	ASSERT_EQ(*(*activity.get_secrets()).get_join(), "join");
	ASSERT_TRUE((*activity.get_secrets()).get_spectate());
	ASSERT_EQ(*(*activity.get_secrets()).get_spectate(), "spectate");
	ASSERT_TRUE((*activity.get_secrets()).get_match());
	ASSERT_EQ(*(*activity.get_secrets()).get_match(), "match");
	ASSERT_TRUE(activity.get_instance());
	ASSERT_EQ(*activity.get_instance(), true);
	ASSERT_EQ(activity.get_flags().get(), 1);
	ASSERT_EQ(activity.get_buttons().size(), buttons.size());
	for (int i = 0; i < buttons.size(); ++i) {
		ASSERT_EQ(activity.get_buttons()[i], buttons[i]) << i;
	}
}

TEST(serialization_activity, object_to_json) {
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
	ASSERT_EQ(activity.to_json(), nlohmann::json::parse("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}").dump());
}

TEST(serialization_activity, func_set_url) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	activity.set_url("edited");
	ASSERT_EQ(*activity.get_url(), "edited");
}
TEST(serialization_activity, func_set_timestamps) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	activity.set_timestamps(timestamps(2,3));
	ASSERT_EQ(*(*activity.get_timestamps()).get_start(), 2);
	ASSERT_EQ(*(*activity.get_timestamps()).get_end(), 3);
}
TEST(serialization_activity, func_set_application_id) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	activity.set_application_id("edited");
	ASSERT_EQ(*activity.get_application_id(), "edited");
}
TEST(serialization_activity, func_set_details) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	activity.set_details("edited");
	ASSERT_EQ(*activity.get_details(), "edited");
}
TEST(serialization_activity, func_set_state) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	activity.set_state("edited");
	ASSERT_EQ(*activity.get_state(), "edited");
}
TEST(serialization_activity, func_set_emoji) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	activity.set_emoji(emoji("edited", "edited", false));
	ASSERT_EQ((*activity.get_emoji()).get_name(), "edited");
	ASSERT_EQ(*(*activity.get_emoji()).get_id(), "edited");
	ASSERT_EQ(*(*activity.get_emoji()).get_animated(), false);
}
TEST(serialization_activity, func_set_party) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	activity.set_party(party(2, party_size(2, 3)));
	ASSERT_EQ(*(*activity.get_party()).get_id(), 2);
	ASSERT_EQ((*(*activity.get_party()).get_size()).get_current_size(), 2);
	ASSERT_EQ((*(*activity.get_party()).get_size()).get_max_size(), 3);
}
TEST(serialization_activity, func_set_assets) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	activity.set_assets(assets("edited", "edited", "edited", "edited"));
	ASSERT_EQ(*(*activity.get_assets()).get_large_image(), "edited");
	ASSERT_EQ(*(*activity.get_assets()).get_large_text(), "edited");
	ASSERT_EQ(*(*activity.get_assets()).get_small_image(), "edited");
	ASSERT_EQ(*(*activity.get_assets()).get_small_text(), "edited");
}
TEST(serialization_activity, func_set_secrets) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	activity.set_secrets(secrets("edited", "edited", "edited"));
	ASSERT_EQ(*(*activity.get_secrets()).get_join(), "edited");
	ASSERT_EQ(*(*activity.get_secrets()).get_spectate(), "edited");
	ASSERT_EQ(*(*activity.get_secrets()).get_match(), "edited");
}
TEST(serialization_activity, func_set_instance) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	activity.set_instance(false);
	ASSERT_EQ(*activity.get_instance(), false);
}
TEST(serialization_activity, func_set_flags) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	activity.set_flags(2);
	ASSERT_EQ(activity.get_flags().get(), 2);
}
TEST(serialization_activity, func_add_button) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	std::vector<discord_ipc::types::button> buttons{ button("label", "url"),button("added", "added") };
	activity.add_button(button("added", "added"));
	ASSERT_EQ(activity.get_buttons().size(), buttons.size());
	for (int i = 0; i < buttons.size(); ++i) {
		ASSERT_EQ(activity.get_buttons()[i], buttons[i]) << i;
	}
}
TEST(serialization_activity, func_remove_button) {
	activity activity = activity::from_json("{\"name\":\"name\",\"type\":1,\"url\":\"url\",\"created_at\":1,\"timestamps\":{\"start\":1,\"end\":2},\"application_id\":\"application_id\",\"details\":\"details\",\"state\":\"state\",\"emoji\":{\"name\":\"name\",\"id\":\"id\",\"animated\":true},\"party\":{\"id\":1,\"size\":[1,2]},\"assets\":{\"large_image\":\"large_image\",\"large_text\":\"large_text\",\"small_image\":\"small_image\",\"small_text\":\"small_text\"},\"secrets\":{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"},\"instance\":true,\"flags\":1,\"buttons\":[{\"label\":\"label\",\"url\":\"url\"}]}");
	std::vector<discord_ipc::types::button> buttons{ };
	activity.remove_button(button("label", "url"));
	ASSERT_EQ(activity.get_buttons().size(), buttons.size());
	for (int i = 0; i < buttons.size(); ++i) {
		ASSERT_EQ(activity.get_buttons()[i], buttons[i]) << i;
	}
}