#include "gtest/gtest.h"
#include "discord-ipc/serialization/party.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_party, json_to_object) {
	party party = party::from_json("{\"id\":1,\"size\":[1,2]}");
	ASSERT_TRUE(party.get_id());
	ASSERT_EQ(*party.get_id(), 1);
	ASSERT_TRUE(party.get_size());
	ASSERT_EQ((*party.get_size()).get_current_size(), 1);
	ASSERT_EQ((*party.get_size()).get_max_size(), 2);
}
TEST(serialization_party, json_to_object1) {
	party party = party::from_json("{\"id\":1}");
	ASSERT_TRUE(party.get_id());
	ASSERT_EQ(*party.get_id(), 1);
	ASSERT_FALSE(party.get_size());
}
TEST(serialization_party, json_to_object2) {
	party party = party::from_json("{\"size\":[1,2]}");
	ASSERT_FALSE(party.get_id());
	ASSERT_TRUE(party.get_size());
	ASSERT_EQ((*party.get_size()).get_current_size(), 1);
	ASSERT_EQ((*party.get_size()).get_max_size(), 2);
}

TEST(serialization_party, object_to_json) {
	party party(1, party_size(1, 2));
	ASSERT_EQ(party.to_json(), nlohmann::json::parse("{\"id\":1,\"size\":[1,2]}").dump());
}
TEST(serialization_party, object_to_json1) {
	party party(1);
	ASSERT_EQ(party.to_json(), nlohmann::json::parse("{\"id\":1}").dump());
}
TEST(serialization_party, object_to_json2) {
	party party(std::nullopt, party_size(1, 2));
	ASSERT_EQ(party.to_json(), nlohmann::json::parse("{\"size\":[1,2]}").dump());
}

TEST(serialization_party, func_set_id) {
	party party = party::from_json("{\"id\":1,\"size\":[1,2]}");
	party.set_id(2);
	ASSERT_TRUE(party.get_id());
	ASSERT_EQ(*party.get_id(), 2);
}
TEST(serialization_party, func_set_size) {
	party party = party::from_json("{\"id\":1,\"size\":[1,2]}");
	party.set_size(party_size(2, 3));
	ASSERT_TRUE(party.get_id());
	ASSERT_EQ((*party.get_size()).get_current_size(), 2);
	ASSERT_EQ((*party.get_size()).get_max_size(), 3);
}