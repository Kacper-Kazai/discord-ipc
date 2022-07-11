#pragma once
#include <string>
#include <optional>

namespace discord_ipc::types {
	struct subscriptions {
		static subscription guilds_status(std::string guild_id);
		static subscription guild_create();
		static subscription channel_create();
		static subscription voice_channel_select();
		static subscription voice_settings_update();
		static subscription voice_state_create(std::string channel_id);
		static subscription voice_state_update(std::string channel_id);
		static subscription voice_state_delete(std::string channel_id);
		static subscription voice_connection_status();
		static subscription message_create(std::string channel_id);
		static subscription message_update(std::string channel_id);
		static subscription message_delete(std::string channel_id);
		static subscription speaking_start(std::string channel_id);
		static subscription speaking_stop(std::string channel_id);
		static subscription notification_create();
		static subscription activity_join();
		static subscription activity_spectate();
		static subscription activity_join_request();
	};
};