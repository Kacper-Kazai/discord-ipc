#include "discord-ipc/serialization/voice_settings.h"
#include <nlohmann/json.hpp>

discord_ipc::types::voice_settings discord_ipc::types::voice_settings::from_json(std::string json) {
	nlohmann::json voice_settings_j = nlohmann::json::parse(json);
	voice_settings voice_settings;
	if (voice_settings_j.contains("input")) voice_settings.set_voice_settings_input(voice_settings_input::from_json(voice_settings_j["input"].get<nlohmann::json>().dump()));
	if (voice_settings_j.contains("output")) voice_settings.set_voice_settings_output(voice_settings_output::from_json(voice_settings_j["output"].get<nlohmann::json>().dump()));
	if (voice_settings_j.contains("mode")) voice_settings.set_voice_settings_mode(voice_settings_mode::from_json(voice_settings_j["mode"].get<nlohmann::json>().dump()));
	if (voice_settings_j.contains("automatic_gain_control")) voice_settings.set_automatic_gain_control(voice_settings_j["automatic_gain_control"]);
	if (voice_settings_j.contains("echo_cancellation")) voice_settings.set_echo_cancellation(voice_settings_j["echo_cancellation"]);
	if (voice_settings_j.contains("noise_suppression")) voice_settings.set_noise_suppression(voice_settings_j["noise_suppression"]);
	if (voice_settings_j.contains("qos")) voice_settings.set_qos(voice_settings_j["qos"]);
	if (voice_settings_j.contains("silence_warning")) voice_settings.set_silence_warning(voice_settings_j["silence_warning"]);
	if (voice_settings_j.contains("deaf")) voice_settings.set_deaf(voice_settings_j["deaf"]);
	if (voice_settings_j.contains("mute")) voice_settings.set_mute(voice_settings_j["mute"]);
	return voice_settings;
}
std::string discord_ipc::types::voice_settings::to_json() const {
	nlohmann::json voice_settings;
	if (this->voice_settings_input) voice_settings["input"] = nlohmann::json::parse((*this->voice_settings_input).to_json());
	if (this->voice_settings_output) voice_settings["output"] = nlohmann::json::parse((*this->voice_settings_output).to_json());
	if (this->voice_settings_mode) voice_settings["mode"] = nlohmann::json::parse((*this->voice_settings_mode).to_json());
	if (this->automatic_gain_control) voice_settings["automatic_gain_control"] = *this->automatic_gain_control;
	if (this->echo_cancellation) voice_settings["echo_cancellation"] = *this->echo_cancellation;
	if (this->noise_suppression) voice_settings["noise_suppression"] = *this->noise_suppression;
	if (this->qos) voice_settings["qos"] = *this->qos;
	if (this->silence_warning) voice_settings["silence_warning"] = *this->silence_warning;
	if (this->deaf) voice_settings["deaf"] = *this->deaf;
	if (this->mute) voice_settings["mute"] = *this->mute;
	return voice_settings.dump();
}