#pragma once
#include "scope.h"
#include <string>
#include <vector>

namespace discord_ipc::types {
	class scopes {
		std::vector<scope> scope_array;
	public:
		scopes() {};
		scopes(std::vector<scope> scope_array) {
			this->scope_array = scope_array;
		};
		std::vector<scope> get_scopes() const {
			return this->scope_array;
		};
		scopes& add(scope scope) {
			scope_array.push_back(scope);
			return *this;
		};
		scopes& remove(scope scope) {
			auto scope_item = std::find(scope_array.begin(), scope_array.end(), scope);
			if (scope_item != scope_array.end()) scope_array.erase(scope_item);
			return *this;
		};
		static scopes from_json(std::string json);
		std::string to_json() const;

		inline static const scope activities_read = "activities.read";
		inline static const scope activities_write = "activities.write";
		inline static const scope applications_builds_read = "applications.builds.read";
		inline static const scope applications_builds_upload = "applications.builds.upload";
		inline static const scope applications_commands = "applications.commands";
		inline static const scope applications_commands_update = "applications.commands.update";
		inline static const scope applications_commands_permissions_update = "applications.commands.permissions.update";
		inline static const scope applications_entitlements = "applications.entitlements";
		inline static const scope applications_store_update = "applications.store.update";
		inline static const scope bot = "bot";
		inline static const scope connections = "connections";
		inline static const scope dm_channels_read = "dm_channels.read";
		inline static const scope email = "email";
		inline static const scope gdm_join = "gdm.join";
		inline static const scope guilds = "guilds";
		inline static const scope guilds_join = "guilds.join";
		inline static const scope guilds_member_read = "guilds.members.read";
		inline static const scope identify = "identify";
		inline static const scope messages_read = "messages.read";
		inline static const scope relationships_read = "relationships.read";
		inline static const scope rpc = "rpc";
		inline static const scope rpc_activities_write = "rpc.activities.write";
		inline static const scope rpc_notifications_read = "rpc.notifications.read";
		inline static const scope rpc_voice_read = "rpc.voice.read";
		inline static const scope rpc_voice_write = "rpc.voice.write";
		inline static const scope voice = "voice";
		inline static const scope webhook_incoming = "webhook.incoming";
	};
};