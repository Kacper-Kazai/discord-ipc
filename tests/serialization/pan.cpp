#include "gtest/gtest.h"
#include "discord-ipc/serialization/pan.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_pan, json_to_object) {
	pan pan = pan::from_json("{\"left\":1,\"right\":0.9}");
	ASSERT_EQ(pan.get_left(), 1);
	ASSERT_EQ(pan.get_right(), (float)0.9);
}

TEST(serialization_pan, object_to_json) {
	pan pan(1, 0);
	ASSERT_EQ(pan.to_json(), nlohmann::json::parse("{\"left\":1.0,\"right\":0.0}").dump());
}

TEST(serialization_pan, func_set_right) {
	pan pan = pan::from_json("{\"left\":0.9,\"right\":1.0}");
	pan.set_right(0.5);
	ASSERT_EQ(pan.get_left(), (float)0.9);
	ASSERT_EQ(pan.get_right(), (float)0.5);
}
TEST(serialization_pan, func_set_left) {
	pan pan = pan::from_json("{\"left\":0.9,\"right\":1.0}");
	pan.set_left(0.5);
	ASSERT_EQ(pan.get_left(), (float)0.5);
	ASSERT_EQ(pan.get_right(), (float)1);
}