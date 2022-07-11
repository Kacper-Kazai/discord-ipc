#include "gtest/gtest.h"
#include "discord-ipc/serialization/vendor.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_vendor, json_to_object) {
	vendor vendor = vendor::from_json("{\"name\":\"name\",\"url\":\"url\"}");
	ASSERT_EQ(vendor.get_name(), "name");
	ASSERT_EQ(vendor.get_url(), "url");
}

TEST(serialization_vendor, object_to_json) {
	vendor vendor("name", "url");
	ASSERT_EQ(vendor.to_json(), nlohmann::json::parse("{\"name\":\"name\",\"url\":\"url\"}").dump());
}