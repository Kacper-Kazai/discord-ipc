#include "discord-ipc/serialization.h"
#include "discord-ipc/serialization/subscriptions.h"
#include <nlohmann/json.hpp>

using discord_ipc::events;

discord_ipc::types::subscription discord_ipc::types::subscriptions::guilds_status(std::string guild_id) {
	nlohmann::json args{
		{"guild_id", guild_id}
	};
	return discord_ipc::types::subscription(events::guild_status, args.dump());
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::guild_create() {
	return discord_ipc::types::subscription(events::guild_create);
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::channel_create(){
	return discord_ipc::types::subscription(events::channel_create);
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::voice_channel_select(){
	return discord_ipc::types::subscription(events::voice_channel_select);
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::voice_settings_update() {
	return discord_ipc::types::subscription(events::voice_settings_update);
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::voice_state_create(std::string channel_id){
	nlohmann::json args{
        {"channel_id", channel_id}
	};
	return discord_ipc::types::subscription(events::voice_state_create, args.dump());
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::voice_state_update(std::string channel_id) {
	nlohmann::json args{
        {"channel_id", channel_id}
	};
	return discord_ipc::types::subscription(events::voice_state_update, args.dump());
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::voice_state_delete(std::string channel_id) {
	nlohmann::json args{
        {"channel_id", channel_id}
	};
	return discord_ipc::types::subscription(events::voice_state_delete, args.dump());
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::voice_connection_status() {
	return discord_ipc::types::subscription(events::voice_connection_status);
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::message_create(std::string channel_id){
	nlohmann::json args{
		{"channel_id", channel_id}
	};
	return discord_ipc::types::subscription(events::message_create, args.dump());
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::message_update(std::string channel_id) {
	nlohmann::json args{
		{"channel_id", channel_id}
	};
	return discord_ipc::types::subscription(events::message_update, args.dump());
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::message_delete(std::string channel_id) {
	nlohmann::json args{
		{"channel_id", channel_id}
	};
	return discord_ipc::types::subscription(events::message_delete, args.dump());
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::speaking_start(std::string channel_id) {
	nlohmann::json args{
		{"channel_id", channel_id}
	};
	return discord_ipc::types::subscription(events::speaking_start, args.dump());
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::speaking_stop(std::string channel_id) {
	nlohmann::json args{
		{"channel_id", channel_id}
	};
	return discord_ipc::types::subscription(events::speaking_stop, args.dump());
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::notification_create(){
	return discord_ipc::types::subscription(events::notification_create);
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::activity_join(){
	return discord_ipc::types::subscription(events::activity_join);
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::activity_spectate() {
	return discord_ipc::types::subscription(events::activity_spectate);
};
discord_ipc::types::subscription discord_ipc::types::subscriptions::activity_join_request() {
	return discord_ipc::types::subscription(events::activity_join_request);
};
