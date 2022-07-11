#include "gtest/gtest.h"
#include "discord-ipc/serialization/certified_device.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_certified_device, json_to_object) {
	certified_device certified_device = certified_device::from_json("{\"type\":\"audioinput\",\"id\":\"id\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"},\"model\":{\"name\":\"name\",\"url\":\"url\"},\"related\":[\"related\"],\"echo_cancellation\":true,\"noise_suppression\":true,\"automatic_gain_control\":true,\"hardware_mute\":true}");
	std::vector<std::string> related{"related"};
	ASSERT_EQ(certified_device.get_type().get(), certified_device_type(certified_device_types::audio_input).get());
	ASSERT_EQ(certified_device.get_id(), "id");
	ASSERT_EQ(certified_device.get_vendor().get_name(), "name");
	ASSERT_EQ(certified_device.get_vendor().get_url(), "url");
	ASSERT_EQ(certified_device.get_model().get_name(), "name");
	ASSERT_EQ(certified_device.get_model().get_url(), "url");
	ASSERT_EQ(certified_device.get_related().size(), related.size());
	for (int i = 0; i < related.size(); ++i) {
		ASSERT_EQ(certified_device.get_related()[i], related[i]) << i;
	}
	ASSERT_TRUE(certified_device.get_echo_cancellation());
	ASSERT_EQ(*certified_device.get_echo_cancellation(), true);
	ASSERT_TRUE(certified_device.get_noise_suppression());
	ASSERT_EQ(*certified_device.get_noise_suppression(), true);
	ASSERT_TRUE(certified_device.get_automatic_gain_control());
	ASSERT_EQ(*certified_device.get_automatic_gain_control(), true);
	ASSERT_TRUE(certified_device.get_hardware_mute());
	ASSERT_EQ(*certified_device.get_hardware_mute(), true);
}
TEST(serialization_certified_device, json_to_object1) {
	certified_device certified_device = certified_device::from_json("{\"type\":\"audioinput\",\"id\":\"id\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"},\"model\":{\"name\":\"name\",\"url\":\"url\"},\"related\":[\"related\"],\"echo_cancellation\":true}");
	std::vector<std::string> related{ "related" };
	ASSERT_EQ(certified_device.get_type().get(), certified_device_type(certified_device_types::audio_input).get());
	ASSERT_EQ(certified_device.get_id(), "id");
	ASSERT_EQ(certified_device.get_vendor().get_name(), "name");
	ASSERT_EQ(certified_device.get_vendor().get_url(), "url");
	ASSERT_EQ(certified_device.get_model().get_name(), "name");
	ASSERT_EQ(certified_device.get_model().get_url(), "url");
	ASSERT_EQ(certified_device.get_related().size(), related.size());
	for (int i = 0; i < related.size(); ++i) {
		ASSERT_EQ(certified_device.get_related()[i], related[i]) << i;
	}
	ASSERT_TRUE(certified_device.get_echo_cancellation());
	ASSERT_EQ(*certified_device.get_echo_cancellation(), true);
	ASSERT_FALSE(certified_device.get_noise_suppression());
	ASSERT_FALSE(certified_device.get_automatic_gain_control());
	ASSERT_FALSE(certified_device.get_hardware_mute());
}
TEST(serialization_certified_device, json_to_object2) {
	certified_device certified_device = certified_device::from_json("{\"type\":\"audioinput\",\"id\":\"id\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"},\"model\":{\"name\":\"name\",\"url\":\"url\"},\"related\":[\"related\"],\"noise_suppression\":true}");
	std::vector<std::string> related{ "related" };
	ASSERT_EQ(certified_device.get_type().get(), certified_device_type(certified_device_types::audio_input).get());
	ASSERT_EQ(certified_device.get_id(), "id");
	ASSERT_EQ(certified_device.get_vendor().get_name(), "name");
	ASSERT_EQ(certified_device.get_vendor().get_url(), "url");
	ASSERT_EQ(certified_device.get_model().get_name(), "name");
	ASSERT_EQ(certified_device.get_model().get_url(), "url");
	ASSERT_EQ(certified_device.get_related().size(), related.size());
	for (int i = 0; i < related.size(); ++i) {
		ASSERT_EQ(certified_device.get_related()[i], related[i]) << i;
	}
	ASSERT_FALSE(certified_device.get_echo_cancellation());
	ASSERT_TRUE(certified_device.get_noise_suppression());
	ASSERT_EQ(*certified_device.get_noise_suppression(), true);
	ASSERT_FALSE(certified_device.get_automatic_gain_control());
	ASSERT_FALSE(certified_device.get_hardware_mute());
}

TEST(serialization_certified_device, object_to_json) {
	certified_device certified_device(
		certified_device_types::audio_input,
		"id",
		vendor("name", "url"),
		model("name", "url"),
		std::vector<std::string>{"related"}
	);
	certified_device
		.set_echo_cancellation(true)
		.set_noise_suppression(true)
		.set_automatic_gain_control(true)
		.set_hardware_mute(true);
	ASSERT_EQ(certified_device.to_json(), nlohmann::json::parse("{\"type\":\"audioinput\",\"id\":\"id\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"},\"model\":{\"name\":\"name\",\"url\":\"url\"},\"related\":[\"related\"],\"echo_cancellation\":true,\"noise_suppression\":true,\"automatic_gain_control\":true,\"hardware_mute\":true}").dump());
}
TEST(serialization_certified_device, object_to_json1) {
	certified_device certified_device(
		certified_device_types::audio_input,
		"id",
		vendor("name", "url"),
		model("name", "url"),
		std::vector<std::string>{"related"}
	);
	certified_device.set_echo_cancellation(true);

	ASSERT_EQ(certified_device.to_json(), nlohmann::json::parse("{\"type\":\"audioinput\",\"id\":\"id\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"},\"model\":{\"name\":\"name\",\"url\":\"url\"},\"related\":[\"related\"],\"echo_cancellation\":true}").dump());
}
TEST(serialization_certified_device, object_to_json2) {
	certified_device certified_device(
		certified_device_types::audio_input,
		"id",
		vendor("name", "url"),
		model("name", "url"),
		std::vector<std::string>{"related"}
	);
	certified_device
		.set_noise_suppression(true);
	ASSERT_EQ(certified_device.to_json(), nlohmann::json::parse("{\"type\":\"audioinput\",\"id\":\"id\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"},\"model\":{\"name\":\"name\",\"url\":\"url\"},\"related\":[\"related\"],\"noise_suppression\":true}").dump());
}

TEST(serialization_certified_device, func_set_echo_cancellation) {
	certified_device certified_device = certified_device::from_json("{\"automatic_gain_control\":true,\"echo_cancellation\":true,\"hardware_mute\":true,\"id\":\"id\",\"model\":{\"name\":\"name\",\"url\":\"url\"},\"noise_suppression\":true,\"related\":[\"related\"],\"type\":\"audioinput\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"}}");
	std::vector<std::string> related{ "related" };
	certified_device.set_echo_cancellation(false);
	ASSERT_EQ(certified_device.get_type().get(), certified_device_type(certified_device_types::audio_input).get());
	ASSERT_EQ(certified_device.get_id(), "id");
	ASSERT_EQ(certified_device.get_vendor().get_name(), "name");
	ASSERT_EQ(certified_device.get_vendor().get_url(), "url");
	ASSERT_EQ(certified_device.get_model().get_name(), "name");
	ASSERT_EQ(certified_device.get_model().get_url(), "url");
	ASSERT_EQ(certified_device.get_related().size(), related.size());
	for (int i = 0; i < related.size(); ++i) {
		ASSERT_EQ(certified_device.get_related()[i], related[i]) << i;
	}
	ASSERT_EQ(*certified_device.get_echo_cancellation(), false);
	ASSERT_EQ(*certified_device.get_noise_suppression(), true);
	ASSERT_EQ(*certified_device.get_automatic_gain_control(), true);
	ASSERT_EQ(*certified_device.get_hardware_mute(), true);
}
TEST(serialization_certified_device, func_set_noise_suppression) {
	certified_device certified_device = certified_device::from_json("{\"automatic_gain_control\":true,\"echo_cancellation\":true,\"hardware_mute\":true,\"id\":\"id\",\"model\":{\"name\":\"name\",\"url\":\"url\"},\"noise_suppression\":true,\"related\":[\"related\"],\"type\":\"audioinput\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"}}");
	std::vector<std::string> related{ "related" }; 
	certified_device.set_noise_suppression(false);
	ASSERT_EQ(certified_device.get_type().get(), certified_device_type(certified_device_types::audio_input).get());
	ASSERT_EQ(certified_device.get_id(), "id");
	ASSERT_EQ(certified_device.get_vendor().get_name(), "name");
	ASSERT_EQ(certified_device.get_vendor().get_url(), "url");
	ASSERT_EQ(certified_device.get_model().get_name(), "name");
	ASSERT_EQ(certified_device.get_model().get_url(), "url");
	ASSERT_EQ(certified_device.get_related().size(), related.size());
	for (int i = 0; i < related.size(); ++i) {
		ASSERT_EQ(certified_device.get_related()[i], related[i]) << i;
	}
	ASSERT_EQ(*certified_device.get_echo_cancellation(), true);
	ASSERT_EQ(*certified_device.get_noise_suppression(), false);
	ASSERT_EQ(*certified_device.get_automatic_gain_control(), true);
	ASSERT_EQ(*certified_device.get_hardware_mute(), true);
}
TEST(serialization_certified_device, func_set_automatic_gain_control) {
	certified_device certified_device = certified_device::from_json("{\"automatic_gain_control\":true,\"echo_cancellation\":true,\"hardware_mute\":true,\"id\":\"id\",\"model\":{\"name\":\"name\",\"url\":\"url\"},\"noise_suppression\":true,\"related\":[\"related\"],\"type\":\"audioinput\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"}}");
	std::vector<std::string> related{ "related" }; 
	certified_device.set_automatic_gain_control(false);
	ASSERT_EQ(certified_device.get_type().get(), certified_device_type(certified_device_types::audio_input).get());
	ASSERT_EQ(certified_device.get_id(), "id");
	ASSERT_EQ(certified_device.get_vendor().get_name(), "name");
	ASSERT_EQ(certified_device.get_vendor().get_url(), "url");
	ASSERT_EQ(certified_device.get_model().get_name(), "name");
	ASSERT_EQ(certified_device.get_model().get_url(), "url");
	ASSERT_EQ(certified_device.get_related().size(), related.size());
	for (int i = 0; i < related.size(); ++i) {
		ASSERT_EQ(certified_device.get_related()[i], related[i]) << i;
	}
	ASSERT_EQ(*certified_device.get_echo_cancellation(), true);
	ASSERT_EQ(*certified_device.get_noise_suppression(), true);
	ASSERT_EQ(*certified_device.get_automatic_gain_control(), false);
	ASSERT_EQ(*certified_device.get_hardware_mute(), true);
}
TEST(serialization_certified_device, func_set_hardware_mute) {
	certified_device certified_device = certified_device::from_json("{\"automatic_gain_control\":true,\"echo_cancellation\":true,\"hardware_mute\":true,\"id\":\"id\",\"model\":{\"name\":\"name\",\"url\":\"url\"},\"noise_suppression\":true,\"related\":[\"related\"],\"type\":\"audioinput\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"}}");
	std::vector<std::string> related{ "related" }; 
	certified_device.set_hardware_mute(false);
	ASSERT_EQ(certified_device.get_type().get(), certified_device_type(certified_device_types::audio_input).get());
	ASSERT_EQ(certified_device.get_id(), "id");
	ASSERT_EQ(certified_device.get_vendor().get_name(), "name");
	ASSERT_EQ(certified_device.get_vendor().get_url(), "url");
	ASSERT_EQ(certified_device.get_model().get_name(), "name");
	ASSERT_EQ(certified_device.get_model().get_url(), "url");
	ASSERT_EQ(certified_device.get_related().size(), related.size());
	for (int i = 0; i < related.size(); ++i) {
		ASSERT_EQ(certified_device.get_related()[i], related[i]) << i;
	}
	ASSERT_EQ(*certified_device.get_echo_cancellation(), true);
	ASSERT_EQ(*certified_device.get_noise_suppression(), true);
	ASSERT_EQ(*certified_device.get_automatic_gain_control(), true);
	ASSERT_EQ(*certified_device.get_hardware_mute(), false);
}
TEST(serialization_certified_device, func_add_related) {
	certified_device certified_device = certified_device::from_json("{\"automatic_gain_control\":true,\"echo_cancellation\":true,\"hardware_mute\":true,\"id\":\"id\",\"model\":{\"name\":\"name\",\"url\":\"url\"},\"noise_suppression\":true,\"related\":[\"related\"],\"type\":\"audioinput\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"}}");
	std::vector<std::string> related{ "related", "added" };
	certified_device.add_related("added");
	ASSERT_EQ(certified_device.get_type().get(), certified_device_type(certified_device_types::audio_input).get());
	ASSERT_EQ(certified_device.get_id(), "id");
	ASSERT_EQ(certified_device.get_vendor().get_name(), "name");
	ASSERT_EQ(certified_device.get_vendor().get_url(), "url");
	ASSERT_EQ(certified_device.get_model().get_name(), "name");
	ASSERT_EQ(certified_device.get_model().get_url(), "url");
	ASSERT_EQ(certified_device.get_related().size(), related.size());
	for (int i = 0; i < related.size(); ++i) {
		ASSERT_EQ(certified_device.get_related()[i], related[i]) << i;
	}
	ASSERT_EQ(*certified_device.get_echo_cancellation(), true);
	ASSERT_EQ(*certified_device.get_noise_suppression(), true);
	ASSERT_EQ(*certified_device.get_automatic_gain_control(), true);
	ASSERT_EQ(*certified_device.get_hardware_mute(), true);
}
TEST(serialization_certified_device, func_remove_related) {
	certified_device certified_device = certified_device::from_json("{\"automatic_gain_control\":true,\"echo_cancellation\":true,\"hardware_mute\":true,\"id\":\"id\",\"model\":{\"name\":\"name\",\"url\":\"url\"},\"noise_suppression\":true,\"related\":[\"related\"],\"type\":\"audioinput\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"}}");
	std::vector<std::string> related{};
	certified_device.remove_related("related");
	ASSERT_EQ(certified_device.get_type().get(), certified_device_type(certified_device_types::audio_input).get());
	ASSERT_EQ(certified_device.get_id(), "id");
	ASSERT_EQ(certified_device.get_vendor().get_name(), "name");
	ASSERT_EQ(certified_device.get_vendor().get_url(), "url");
	ASSERT_EQ(certified_device.get_model().get_name(), "name");
	ASSERT_EQ(certified_device.get_model().get_url(), "url");
	ASSERT_EQ(certified_device.get_related().size(), related.size());
	for (int i = 0; i < related.size(); ++i) {
		ASSERT_EQ(certified_device.get_related()[i], related[i]) << i;
	}
	ASSERT_EQ(*certified_device.get_echo_cancellation(), true);
	ASSERT_EQ(*certified_device.get_noise_suppression(), true);
	ASSERT_EQ(*certified_device.get_automatic_gain_control(), true);
	ASSERT_EQ(*certified_device.get_hardware_mute(), true);
}