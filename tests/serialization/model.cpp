#include "gtest/gtest.h"
#include "discord-ipc/serialization/model.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_model, json_to_object) {
	model model = model::from_json("{\"name\":\"name\",\"url\":\"url\"}");
	ASSERT_EQ(model.get_name(), "name");
	ASSERT_EQ(model.get_url(), "url");
}

TEST(serialization_model, object_to_json) {
	model model("name", "url");
	ASSERT_EQ(model.to_json(), nlohmann::json::parse("{\"name\":\"name\",\"url\":\"url\"}").dump());
}