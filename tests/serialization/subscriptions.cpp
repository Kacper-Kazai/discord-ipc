#include "gtest/gtest.h"
#include "discord-ipc/serialization/subscription.h"
#include "discord-ipc/serialization/subscriptions.h"
#include "discord-ipc/serialization.h"
#include <optional>
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;
using discord_ipc::events;

TEST(serialization_subscriptions, guild_status) {
	subscription subscription = subscriptions::guilds_status("id");
	ASSERT_EQ(subscription.get_evt(), events::guild_status);
	ASSERT_EQ(subscription.args_to_json(), nlohmann::json::parse("{\"guild_id\":\"id\"}").dump());
}
TEST(serialization_subscription, guild_create) {
	subscription subscription = subscriptions::guild_create();
	ASSERT_EQ(subscription.get_evt(), events::guild_create);
	ASSERT_FALSE(subscription.args_to_json());
}
TEST(serialization_subscription, channel_create) {
	subscription subscription = subscriptions::channel_create();
	ASSERT_EQ(subscription.get_evt(), events::channel_create);
	ASSERT_FALSE(subscription.args_to_json());
}
TEST(serialization_subscription, voice_channel_select) {
	subscription subscription = subscriptions::voice_channel_select();
	ASSERT_EQ(subscription.get_evt(), events::voice_channel_select);
	ASSERT_FALSE(subscription.args_to_json());
}
TEST(serialization_subscription, voice_state_create) {
	subscription subscription = subscriptions::voice_state_create("id");
	ASSERT_EQ(subscription.get_evt(), events::voice_state_create);
	ASSERT_EQ(subscription.args_to_json(), nlohmann::json::parse("{\"channel_id\":\"id\"}").dump());
}
TEST(serialization_subscription, voice_state_update) {
	subscription subscription = subscriptions::voice_state_update("id");
	ASSERT_EQ(subscription.get_evt(), events::voice_state_update);
	ASSERT_EQ(subscription.args_to_json(), nlohmann::json::parse("{\"channel_id\":\"id\"}").dump());
}
TEST(serialization_subscription, voice_state_delete) {
	subscription subscription = subscriptions::voice_state_delete("id");
	ASSERT_EQ(subscription.get_evt(), events::voice_state_delete);
	ASSERT_EQ(subscription.args_to_json(), nlohmann::json::parse("{\"channel_id\":\"id\"}").dump());
}
TEST(serialization_subscription, voice_connection_status) {
	subscription subscription = subscriptions::voice_connection_status();
	ASSERT_EQ(subscription.get_evt(), events::voice_connection_status);
	ASSERT_FALSE(subscription.args_to_json());
}
TEST(serialization_subscription, message_create) {
	subscription subscription = subscriptions::message_create("id");
	ASSERT_EQ(subscription.get_evt(), events::message_create);
	ASSERT_EQ(subscription.args_to_json(), nlohmann::json::parse("{\"channel_id\":\"id\"}").dump());
}
TEST(serialization_subscription, message_update) {
	subscription subscription = subscriptions::message_update("id");
	ASSERT_EQ(subscription.get_evt(), events::message_update);
	ASSERT_EQ(subscription.args_to_json(), nlohmann::json::parse("{\"channel_id\":\"id\"}").dump());
}
TEST(serialization_subscription, message_delete) {
	subscription subscription = subscriptions::message_delete("id");
	ASSERT_EQ(subscription.get_evt(), events::message_delete);
	ASSERT_EQ(subscription.args_to_json(), nlohmann::json::parse("{\"channel_id\":\"id\"}").dump());
}
TEST(serialization_subscription, speaking_start) {
	subscription subscription = subscriptions::speaking_start("id");
	ASSERT_EQ(subscription.get_evt(), events::speaking_start);
	ASSERT_EQ(subscription.args_to_json(), nlohmann::json::parse("{\"channel_id\":\"id\"}").dump());
}
TEST(serialization_subscription, speaking_stop) {
	subscription subscription = subscriptions::speaking_stop("id");
	ASSERT_EQ(subscription.get_evt(), events::speaking_stop);
	ASSERT_EQ(subscription.args_to_json(), nlohmann::json::parse("{\"channel_id\":\"id\"}").dump());
}
TEST(serialization_subscription, notification_create) {
	subscription subscription = subscriptions::notification_create();
	ASSERT_EQ(subscription.get_evt(), events::notification_create);
	ASSERT_FALSE(subscription.args_to_json());
}
TEST(serialization_subscription, activity_join) {
	subscription subscription = subscriptions::activity_join();
	ASSERT_EQ(subscription.get_evt(), events::activity_join);
	ASSERT_FALSE(subscription.args_to_json());
}
TEST(serialization_subscription, activity_spectate) {
	subscription subscription = subscriptions::activity_spectate();
	ASSERT_EQ(subscription.get_evt(), events::activity_spectate);
	ASSERT_FALSE(subscription.args_to_json());
}
TEST(serialization_subscription, activity_join_request) {
	subscription subscription = subscriptions::activity_join_request();
	ASSERT_EQ(subscription.get_evt(), events::activity_join_request);
	ASSERT_FALSE(subscription.args_to_json());
}