#include "gtest/gtest.h"
#include "discord-ipc/serialization/party_size.h"
#include <vector>
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_party_size, json_to_object) {
	party_size party_size = party_size::from_json("[1,2]");
	ASSERT_EQ(party_size.get_current_size(), 1);
	ASSERT_EQ(party_size.get_max_size(), 2);
}

TEST(serialization_party_size, object_to_json) {
	party_size party_size(1, 2);
	ASSERT_EQ(party_size.to_json(), nlohmann::json::parse("[1,2]").dump());
}