#include "gtest/gtest.h"
#include "discord-ipc/serialization/certified_devices.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_certified_devices, json_to_object) {
	certified_devices certified_devices = certified_devices::from_json("{\"buttons\":[{\"type\":\"audioinput\",\"id\":\"id\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"},\"model\":{\"name\":\"name\",\"url\":\"url\"},\"related\":[\"related\"],\"echo_cancellation\":true,\"noise_suppression\":true,\"automatic_gain_control\":true,\"hardware_mute\":true}]}");
	std::vector<std::string> related{ "related" };
	ASSERT_EQ(certified_devices.get_devices().size(), 1);
	ASSERT_EQ(certified_devices.get_devices()[0].get_type().get(), certified_device_type(certified_device_types::audio_input).get());
	ASSERT_EQ(certified_devices.get_devices()[0].get_id(), "id");
	ASSERT_EQ(certified_devices.get_devices()[0].get_vendor().get_name(), "name");
	ASSERT_EQ(certified_devices.get_devices()[0].get_vendor().get_url(), "url");
	ASSERT_EQ(certified_devices.get_devices()[0].get_model().get_name(), "name");
	ASSERT_EQ(certified_devices.get_devices()[0].get_model().get_url(), "url");
	ASSERT_EQ(certified_devices.get_devices()[0].get_related().size(), related.size());
	for (int i = 0; i < related.size(); ++i) {
		ASSERT_EQ(certified_devices.get_devices()[0].get_related()[i], related[i]) << i;
	}
	ASSERT_TRUE(certified_devices.get_devices()[0].get_echo_cancellation());
	ASSERT_EQ(*certified_devices.get_devices()[0].get_echo_cancellation(), true);
	ASSERT_TRUE(certified_devices.get_devices()[0].get_noise_suppression());
	ASSERT_EQ(*certified_devices.get_devices()[0].get_noise_suppression(), true);
	ASSERT_TRUE(certified_devices.get_devices()[0].get_automatic_gain_control());
	ASSERT_EQ(*certified_devices.get_devices()[0].get_automatic_gain_control(), true);
	ASSERT_TRUE(certified_devices.get_devices()[0].get_hardware_mute());
	ASSERT_EQ(*certified_devices.get_devices()[0].get_hardware_mute(), true);
}

TEST(serialization_certified_devices, object_to_json) {
	std::vector<certified_device> devices;
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
	devices.push_back(certified_device);
	certified_devices certified_devices(devices);
	ASSERT_EQ(certified_devices.to_json(), nlohmann::json::parse("{\"buttons\":[{\"type\":\"audioinput\",\"id\":\"id\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"},\"model\":{\"name\":\"name\",\"url\":\"url\"},\"related\":[\"related\"],\"echo_cancellation\":true,\"noise_suppression\":true,\"automatic_gain_control\":true,\"hardware_mute\":true}]}").dump());
}

TEST(serialization_certified_devices, func_add) {
	certified_devices certified_devices = certified_devices::from_json("{\"buttons\":[{\"type\":\"audioinput\",\"id\":\"id\",\"vendor\":{\"name\":\"name\",\"url\":\"url\"},\"model\":{\"name\":\"name\",\"url\":\"url\"},\"related\":[\"related\"],\"echo_cancellation\":true,\"noise_suppression\":true,\"automatic_gain_control\":true,\"hardware_mute\":true}]}");
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
}
TEST(serialization_certified_devices, func_remove) {

}