#include "gtest/gtest.h"
#include "discord-ipc/serialization.h"

using discord_ipc::commands;
using discord_ipc::events;

TEST(serialization, commands) {
	ASSERT_EQ(commands::dispatch, "DISPATCH");
	ASSERT_EQ(commands::authorize, "AUTHORIZE");
	ASSERT_EQ(commands::authenticate, "AUTHENTICATE");
	ASSERT_EQ(commands::get_guild, "GET_GUILD");
	ASSERT_EQ(commands::get_guilds, "GET_GUILDS");
	ASSERT_EQ(commands::get_channel, "GET_CHANNEL");
	ASSERT_EQ(commands::get_channels, "GET_CHANNELS");
	ASSERT_EQ(commands::subscribe, "SUBSCRIBE");
	ASSERT_EQ(commands::unsubscribe, "UNSUBSCRIBE");
	ASSERT_EQ(commands::set_user_voice_settings, "SET_USER_VOICE_SETTINGS");
	ASSERT_EQ(commands::select_voice_channel, "SELECT_VOICE_CHANNEL");
	ASSERT_EQ(commands::get_selected_voice_channel, "GET_SELECTED_VOICE_CHANNEL");
	ASSERT_EQ(commands::select_text_channel, "SELECT_TEXT_CHANNEL");
	ASSERT_EQ(commands::get_voice_settings, "GET_VOICE_SETTINGS");
	ASSERT_EQ(commands::set_voice_settings, "SET_VOICE_SETTINGS");
	ASSERT_EQ(commands::set_certified_devices, "SET_CERTIFIED_DEVICES");
	ASSERT_EQ(commands::set_activity, "SET_ACTIVITY");
	ASSERT_EQ(commands::send_activity_join_invite, "SEND_ACTIVITY_JOIN_INVITE");
	ASSERT_EQ(commands::close_activity_request, "CLOSE_ACTIVITY_REQUEST");
}
TEST(serialization, events) {
	ASSERT_EQ(events::ready, "READY");
	ASSERT_EQ(events::error, "ERROR");
	ASSERT_EQ(events::guild_status, "GUILD_STATUS");
	ASSERT_EQ(events::guild_create, "GUILD_CREATE");
	ASSERT_EQ(events::channel_create, "CHANNEL_CREATE");
	ASSERT_EQ(events::voice_channel_select, "VOICE_CHANNEL_SELECT");
	ASSERT_EQ(events::voice_state_create, "VOICE_STATE_CREATE");
	ASSERT_EQ(events::voice_state_update, "VOICE_STATE_UPDATE");
	ASSERT_EQ(events::voice_state_delete, "VOICE_STATE_DELETE");
	ASSERT_EQ(events::voice_settings_update, "VOICE_SETTINGS_UPDATE");
	ASSERT_EQ(events::voice_connection_status, "VOICE_CONNECTION_STATUS");
	ASSERT_EQ(events::speaking_start, "SPEAKING_START");
	ASSERT_EQ(events::speaking_stop, "SPEAKING_STOP");
	ASSERT_EQ(events::message_create, "MESSAGE_CREATE");
	ASSERT_EQ(events::message_update, "MESSAGE_UPDATE");
	ASSERT_EQ(events::message_delete, "MESSAGE_DELETE");
	ASSERT_EQ(events::notification_create, "NOTIFICATION_CREATE");
	ASSERT_EQ(events::activity_join, "ACTIVITY_JOIN");
	ASSERT_EQ(events::activity_spectate, "ACTIVITY_SPECTATE");
	ASSERT_EQ(events::activity_join_request, "ACTIVITY_JOIN_REQUEST");
}