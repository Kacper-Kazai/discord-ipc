#include "discord-ipc/serialization.h"
#include <nlohmann/json.hpp>

using nlohmann::json;

std::string write_json_error(int code, std::string message) {
    json writer = {
        {"code", code},
        {"message", message}
    };

    return writer.dump();
};

void write_nonce_to_packet(packet& packet, std::string& nonce) {
    json data_json = json::parse(packet.data);

    data_json["nonce"] = nonce;

    packet.data = data_json.dump();
};

packet create_packet(opcode opcode, json* data) {
    packet p;
    p.opcode = opcode;
    p.data = data->dump();
    return p;
};
packet create_packet(json* data) {
    return create_packet(opcode::frame, data);;
};

packet discord_ipc::packets::handshake(int ipc_version, std::string application_id) {
    json data;
    data["v"] = ipc_version;
    data["client_id"] = application_id;
    return create_packet(opcode::handshake, &data);
};
packet discord_ipc::packets::authorize(std::string application_id, types::scopes& scopes) {
    json data;
    data["cmd"] = commands::authorize;
    data["args"]["client_id"] = application_id;
    data["args"]["scopes"] = json::parse(scopes.to_json());
    return create_packet(&data);
};
packet discord_ipc::packets::authenticate(std::string access_token) {
    json data;
    data["cmd"] = commands::authenticate;
    data["args"]["access_token"] = access_token;
    return create_packet(&data);
};
packet discord_ipc::packets::get_guilds() {
    json data;
    data["cmd"] = commands::get_guilds;
    return create_packet(&data);
};
packet discord_ipc::packets::get_guild(std::string guild_id, std::optional<int> timeout) {
    json data;
    data["cmd"] = commands::get_guild;
    data["args"]["guild_id"] = guild_id;
    if (timeout) data["args"]["timeout"] = *timeout;
    return create_packet(&data);
};
packet discord_ipc::packets::get_channel(std::string channel_id) {
    json data;
    data["cmd"] = commands::get_channel;
    data["args"]["channel_id"] = channel_id;
    return create_packet(&data);
};
packet discord_ipc::packets::get_channels(std::string guild_id) {
    json data;
    data["cmd"] = commands::get_channels;
    data["args"]["guild_id"] = guild_id;
    return create_packet(&data);
};
packet discord_ipc::packets::set_user_voice_settings(types::user_voice_settings user_voice_settings) {
    json data;
    data["cmd"] = commands::set_user_voice_settings;
    data["args"] = json::parse(user_voice_settings.to_json());
    return create_packet(&data);
};
packet discord_ipc::packets::select_voice_channel(std::optional<std::string> channel_id, std::optional<int> timeout, std::optional<bool> force) {
    json data;
    data["cmd"] = commands::select_voice_channel;
    if(channel_id) data["args"]["channel_id"] = *channel_id;
    if(timeout) data["args"]["timeout"] = *timeout;
    if(force) data["args"]["force"] = *force;
    return create_packet(&data);
};
packet discord_ipc::packets::get_selected_voice_channel() {
    json data;
    data["cmd"] = commands::get_selected_voice_channel;
    return create_packet(&data);
};
packet discord_ipc::packets::select_text_channel(std::string channel_id, std::optional<int> timeout) {
    json data;
    data["cmd"] = commands::select_text_channel;
    data["args"]["channel_id"] = channel_id;
    if (timeout) data["args"]["timeout"] = *timeout;
    return create_packet(&data);
};
packet discord_ipc::packets::get_voice_settings() {
    json data;
    data["cmd"] = commands::get_voice_settings;
    return create_packet(&data);
};
packet discord_ipc::packets::set_voice_settings(types::voice_settings voice_settings) {
    json data;
    data["cmd"] = commands::set_voice_settings;
    data["args"] = json::parse(voice_settings.to_json());
    return create_packet(&data);
};
packet discord_ipc::packets::subscribe(types::subscription subscription) {
    json data;
    data["cmd"] = commands::subscribe;
    data["evt"] = subscription.get_evt();
    if (subscription.args_to_json()) data["args"] = json::parse(*subscription.args_to_json());
    return create_packet(&data);
};
packet discord_ipc::packets::unsubscribe(types::subscription subscription) {
    json data;
    data["cmd"] = commands::unsubscribe;
    data["evt"] = subscription.get_evt();
    if (subscription.args_to_json()) data["args"] = json::parse(*subscription.args_to_json());
    return create_packet(&data);
};
packet discord_ipc::packets::set_certified_devices(types::certified_devices certified_devices) {
    json data;
    data["cmd"] = commands::set_certified_devices;
    data["evt"] = certified_devices.to_json();
    return create_packet(&data);
};
packet discord_ipc::packets::set_activity(types::action action) {
    json data;
    data["cmd"] = commands::set_activity;
    data["arg"] = json::parse(action.to_json());
    return create_packet(&data);
};
packet discord_ipc::packets::send_activity_join_invite(std::string user_id) {
    json data;
    data["cmd"] = commands::send_activity_join_invite;
    data["args"]["user_id"] = user_id;
    return create_packet(&data);
};
packet discord_ipc::packets::close_activity_request(std::string user_id) {
    json data;
    data["cmd"] = commands::close_activity_request;
    data["args"]["user_id"] = user_id;
    return create_packet(&data);
};