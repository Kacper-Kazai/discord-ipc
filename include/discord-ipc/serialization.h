#pragma once
#include "discord-ipc/packet.h"
#include "discord-ipc/serialization/scopes.h"
#include "discord-ipc/serialization/user_voice_settings.h"
#include "discord-ipc/serialization/voice_settings.h"
#include "discord-ipc/serialization/subscription.h"
#include "discord-ipc/serialization/certified_devices.h"
#include "discord-ipc/serialization/action.h"
#include <optional>

namespace discord_ipc {
	struct commands {
		inline static const std::string dispatch = "DISPATCH";
		inline static const std::string authorize = "AUTHORIZE";
		inline static const std::string authenticate = "AUTHENTICATE";
		inline static const std::string get_guild = "GET_GUILD";
		inline static const std::string get_guilds = "GET_GUILDS";
		inline static const std::string get_channel = "GET_CHANNEL";
		inline static const std::string get_channels = "GET_CHANNELS";
		inline static const std::string subscribe = "SUBSCRIBE";
		inline static const std::string unsubscribe = "UNSUBSCRIBE";
		inline static const std::string set_user_voice_settings = "SET_USER_VOICE_SETTINGS";
		inline static const std::string select_voice_channel = "SELECT_VOICE_CHANNEL";
		inline static const std::string get_selected_voice_channel = "GET_SELECTED_VOICE_CHANNEL";
		inline static const std::string select_text_channel = "SELECT_TEXT_CHANNEL";
		inline static const std::string get_voice_settings = "GET_VOICE_SETTINGS";
		inline static const std::string set_voice_settings = "SET_VOICE_SETTINGS";
		inline static const std::string set_certified_devices = "SET_CERTIFIED_DEVICES";
		inline static const std::string set_activity = "SET_ACTIVITY";
		inline static const std::string send_activity_join_invite = "SEND_ACTIVITY_JOIN_INVITE";
		inline static const std::string close_activity_request = "CLOSE_ACTIVITY_REQUEST";
	};
	struct events {
		inline static const std::string ready = "READY";
		inline static const std::string error = "ERROR";
		inline static const std::string guild_status = "GUILD_STATUS";
		inline static const std::string guild_create = "GUILD_CREATE";
		inline static const std::string channel_create = "CHANNEL_CREATE";
		inline static const std::string voice_channel_select = "VOICE_CHANNEL_SELECT";
		inline static const std::string voice_settings_update = "VOICE_SETTINGS_UPDATE";
		inline static const std::string voice_state_create = "VOICE_STATE_CREATE";
		inline static const std::string voice_state_update = "VOICE_STATE_UPDATE";
		inline static const std::string voice_state_delete = "VOICE_STATE_DELETE";
		inline static const std::string voice_connection_status = "VOICE_CONNECTION_STATUS";
		inline static const std::string message_create = "MESSAGE_CREATE";
		inline static const std::string message_update = "MESSAGE_UPDATE";
		inline static const std::string message_delete = "MESSAGE_DELETE";
		inline static const std::string speaking_start = "SPEAKING_START";
		inline static const std::string speaking_stop = "SPEAKING_STOP";
		inline static const std::string notification_create = "NOTIFICATION_CREATE";
		inline static const std::string activity_join = "ACTIVITY_JOIN";
		inline static const std::string activity_spectate = "ACTIVITY_SPECTATE";
		inline static const std::string activity_join_request = "ACTIVITY_JOIN_REQUEST";
	};

	struct packets {
		static packet handshake(int ipc_version, std::string application_id);
		static packet authorize(std::string application_id, types::scopes& scopes);
		static packet authenticate(std::string access_token);
		static packet get_guilds();
		static packet get_guild(std::string guild_id, std::optional<int> timeout = std::nullopt);
		static packet get_channel(std::string channel_id);
		static packet get_channels(std::string guild_id);
		static packet set_user_voice_settings(types::user_voice_settings user_voice_settings);
		static packet select_voice_channel(std::optional<std::string> channel_id = std::nullopt, std::optional<int> timeout = std::nullopt, std::optional<bool> force = std::nullopt);
		static packet get_selected_voice_channel();
		static packet select_text_channel(std::string channel_id, std::optional<int> timeout = std::nullopt);
		static packet get_voice_settings();
		static packet set_voice_settings(types::voice_settings voice_settings);
		static packet subscribe(types::subscription subscription);
		static packet unsubscribe(types::subscription subscription);
		static packet set_certified_devices(types::certified_devices certified_devices);
		static packet set_activity(types::action action);
		static packet send_activity_join_invite(std::string user_id);
		static packet close_activity_request(std::string user_id);
	};
};

std::string write_json_error(int code, std::string message);
void write_nonce_to_packet(packet& packet, std::string& nonce);	
