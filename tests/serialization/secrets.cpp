#include "gtest/gtest.h"
#include "discord-ipc/serialization/secrets.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_secrets, json_to_object) {
	secrets secrets = secrets::from_json("{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"}");
	ASSERT_TRUE(secrets.get_join());
	ASSERT_EQ(*secrets.get_join(), "join");
	ASSERT_TRUE(secrets.get_spectate());
	ASSERT_EQ(*secrets.get_spectate(), "spectate");
	ASSERT_TRUE(secrets.get_match());
	ASSERT_EQ(*secrets.get_match(), "match");
}
TEST(serialization_secrets, json_to_object1) {
	secrets secrets = secrets::from_json("{\"join\":\"join\"}");
	ASSERT_TRUE(secrets.get_join());
	ASSERT_EQ(*secrets.get_join(), "join");
	ASSERT_FALSE(secrets.get_spectate());
	ASSERT_FALSE(secrets.get_match());
}
TEST(serialization_secrets, json_to_object2) {
	secrets secrets = secrets::from_json("{\"spectate\":\"spectate\"}");
	ASSERT_FALSE(secrets.get_join());
	ASSERT_TRUE(secrets.get_spectate());
	ASSERT_EQ(*secrets.get_spectate(), "spectate");
	ASSERT_FALSE(secrets.get_match());
}


TEST(serialization_secrets, object_to_json) {
	secrets secrets("join", "spectate", "match");
	ASSERT_EQ(secrets.to_json(), nlohmann::json::parse("{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"}").dump());
}
TEST(serialization_secrets, object_to_json1) {
	secrets secrets("join");
	ASSERT_EQ(secrets.to_json(), nlohmann::json::parse("{\"join\":\"join\"}").dump());
}
TEST(serialization_secrets, object_to_json2) {
	secrets secrets(std::nullopt, "spectate");
	ASSERT_EQ(secrets.to_json(), nlohmann::json::parse("{\"spectate\":\"spectate\"}").dump());
}

TEST(serialization_secrets, func_set_join) {
	secrets secrets = secrets::from_json("{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"}");
	secrets.set_join("edited");
	ASSERT_TRUE(secrets.get_join());
	ASSERT_EQ(*secrets.get_join(), "edited");
}
TEST(serialization_secrets, func_set_spectate) {
	secrets secrets = secrets::from_json("{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"}");
	secrets.set_spectate("edited");
	ASSERT_TRUE(secrets.get_spectate());
	ASSERT_EQ(*secrets.get_spectate(), "edited");
}
TEST(serialization_secrets, func_set_match) {
	secrets secrets = secrets::from_json("{\"join\":\"join\",\"spectate\":\"spectate\",\"match\":\"match\"}");
	secrets.set_match("edited");
	ASSERT_TRUE(secrets.get_match());
	ASSERT_EQ(*secrets.get_match(), "edited");
}