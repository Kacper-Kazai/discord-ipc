#include "gtest/gtest.h"
#include "discord-ipc/serialization/scope.h"
#include "discord-ipc/serialization/scopes.h"
#include <vector>
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_scopes, defaults_activities_read) {
	ASSERT_EQ((scope(scopes::activities_read)).get(), "activities.read");
}
TEST(serialization_scopes, defaults_activities_write) {
	ASSERT_EQ((scope(scopes::activities_write)).get(), "activities.write");
}
TEST(serialization_scopes, defaults_applications_builds_read) {
	ASSERT_EQ((scope(scopes::applications_builds_read)).get(), "applications.builds.read");
}
TEST(serialization_scopes, defaults_applications_builds_upload) {
	ASSERT_EQ((scope(scopes::applications_builds_upload)).get(), "applications.builds.upload");
}
TEST(serialization_scopes, defaults_applications_commands) {
	ASSERT_EQ((scope(scopes::applications_commands)).get(), "applications.commands");
}
TEST(serialization_scopes, defaults_applications_commands_update) {
	ASSERT_EQ((scope(scopes::applications_commands_update)).get(), "applications.commands.update");
}
TEST(serialization_scopes, defaults_applications_commands_permissions_update) {
	ASSERT_EQ((scope(scopes::applications_commands_permissions_update)).get(), "applications.commands.permissions.update");
}
TEST(serialization_scopes, defaults_applications_entitlements) {
	ASSERT_EQ((scope(scopes::applications_entitlements)).get(), "applications.entitlements");
}
TEST(serialization_scopes, defaults_applications_store_update) {
	ASSERT_EQ((scope(scopes::applications_store_update)).get(), "applications.store.update");
}
TEST(serialization_scopes, defaults_bot) {
	ASSERT_EQ((scope(scopes::bot)).get(), "bot");
}
TEST(serialization_scopes, defaults_connections) {
	ASSERT_EQ((scope(scopes::connections)).get(), "connections");
}
TEST(serialization_scopes, defaults_dm_channels_read) {
	ASSERT_EQ((scope(scopes::dm_channels_read)).get(), "dm_channels.read");
}
TEST(serialization_scopes, defaults_email) {
	ASSERT_EQ((scope(scopes::email)).get(), "email");
}
TEST(serialization_scopes, defaults_gmd_join) {
	ASSERT_EQ((scope(scopes::gdm_join)).get(), "gdm.join");
}
TEST(serialization_scopes, defaults_guilds) {
	ASSERT_EQ((scope(scopes::guilds)).get(), "guilds");
}
TEST(serialization_scopes, defaults_guilds_join) {
	ASSERT_EQ((scope(scopes::guilds_join)).get(), "guilds.join");
}
TEST(serialization_scopes, defaults_guilds_members_read) {
	ASSERT_EQ((scope(scopes::guilds_member_read)).get(), "guilds.members.read");
}
TEST(serialization_scopes, defaults_identify) {
	ASSERT_EQ((scope(scopes::identify)).get(), "identify");
}
TEST(serialization_scopes, defaults_messages_read) {
	ASSERT_EQ((scope(scopes::messages_read)).get(), "messages.read");
}
TEST(serialization_scopes, defaults_relationships_read) {
	ASSERT_EQ((scope(scopes::relationships_read)).get(), "relationships.read");
}
TEST(serialization_scopes, defaults_rpc) {
	ASSERT_EQ((scope(scopes::rpc)).get(), "rpc");
}
TEST(serialization_scopes, defaults_rpc_activities_write) {
	ASSERT_EQ((scope(scopes::rpc_activities_write)).get(), "rpc.activities.write");
}
TEST(serialization_scopes, defaults_rpc_notifications_read) {
	ASSERT_EQ((scope(scopes::rpc_notifications_read)).get(), "rpc.notifications.read");
}
TEST(serialization_scopes, defaults_rpc_voice_read) {
	ASSERT_EQ((scope(scopes::rpc_voice_read)).get(), "rpc.voice.read");
}
TEST(serialization_scopes, defaults_rpc_voice_write) {
	ASSERT_EQ((scope(scopes::rpc_voice_write)).get(), "rpc.voice.write");
}
TEST(serialization_scopes, defaults_voice) {
	ASSERT_EQ((scope(scopes::voice)).get(), "voice");
}
TEST(serialization_scopes, defaults_webhook_incoming) {
	ASSERT_EQ((scope(scopes::webhook_incoming)).get(), "webhook.incoming");
}

TEST(serialization_scopes, object_to_json) {
	std::vector<scope> scope_array{ scopes::activities_read };
	scopes scopes(scope_array);
	ASSERT_EQ(scopes.to_json(), nlohmann::json::parse("[\"activities.read\"]").dump());
}
TEST(serialization_scopes, object_to_json1) {
	std::vector<scope> scope_array{ scopes::activities_read, scopes::activities_write };
	scopes scopes(scope_array);
	ASSERT_EQ(scopes.to_json(), nlohmann::json::parse("[\"activities.read\",\"activities.write\"]").dump());
}

TEST(serialization_scopes, json_to_object) {
	scopes scopes = scopes::from_json("[\"activities.read\"]");
	std::vector<scope> scope_array{ scopes::activities_read };
	ASSERT_EQ(scopes.get_scopes().size(), scope_array.size());
	for (int i = 0; i < scope_array.size(); ++i) {
		ASSERT_EQ(scopes.get_scopes()[i], scope_array[i]) << i;
	}
}
TEST(serialization_scopes, json_to_object1) {
	scopes scopes = scopes::from_json("[\"activities.read\", \"activities.write\"]");
	std::vector<scope> scope_array{ scopes::activities_read, scopes::activities_write };
	ASSERT_EQ(scopes.get_scopes().size(), scope_array.size());
	for (int i = 0; i < scope_array.size(); ++i) {
		ASSERT_EQ(scopes.get_scopes()[i], scope_array[i]) << i;
	}
}

TEST(serialization_scopes, func_add) {
	scopes scopes = scopes::from_json("[\"activities.read\"]");
	scopes.add(scopes::activities_write);
	ASSERT_EQ(scopes.to_json(), nlohmann::json::parse("[\"activities.read\",\"activities.write\"]").dump());
}
TEST(serialization_scopes, func_remove) {
	scopes scopes = scopes::from_json("[\"activities.read\"]");
	scopes.remove(scopes::activities_read);
	ASSERT_EQ(scopes.to_json(), nlohmann::json::parse("[]").dump());
}