#pragma once
#include "voice_settings_input.h"
#include "voice_settings_output.h"
#include "voice_settings_mode.h"
#include <string>
#include <optional>

namespace discord_ipc::types {
	class voice_settings {
		std::optional<discord_ipc::types::voice_settings_input> voice_settings_input;
		std::optional<discord_ipc::types::voice_settings_output> voice_settings_output;
		std::optional<discord_ipc::types::voice_settings_mode> voice_settings_mode;
		std::optional<bool> automatic_gain_control;
		std::optional<bool> echo_cancellation;
		std::optional<bool> noise_suppression;
		std::optional<bool> qos;
		std::optional<bool> silence_warning;
		std::optional<bool> deaf;
		std::optional<bool> mute;
	public:
		std::optional<discord_ipc::types::voice_settings_input> get_voice_settings_input() const {
			return this->voice_settings_input;
		};
		std::optional<discord_ipc::types::voice_settings_output> get_voice_settings_output() const {
			return this->voice_settings_output;
		};
		std::optional<discord_ipc::types::voice_settings_mode> get_voice_settings_mode() const {
			return this->voice_settings_mode;
		};
		std::optional<bool> get_automatic_gain_control() const {
			return this->automatic_gain_control;
		};
		std::optional<bool> get_echo_cancellation() const {
			return this->echo_cancellation;
		};
		std::optional<bool> get_noise_suppression() const {
			return this->noise_suppression;
		};
		std::optional<bool> get_qos() const {
			return this->qos;
		};
		std::optional<bool> get_silence_warning() const {
			return this->silence_warning;
		};
		std::optional<bool> get_deaf() const {
			return this->deaf;
		};
		std::optional<bool> get_mute() const {
			return this->mute;
		};
		voice_settings set_voice_settings_input(discord_ipc::types::voice_settings_input voice_settings_input) {
			this->voice_settings_input = voice_settings_input;
			return *this;
		};
		voice_settings set_voice_settings_output(discord_ipc::types::voice_settings_output voice_settings_output) {
			this->voice_settings_output = voice_settings_output;
			return *this;
		};
		voice_settings set_voice_settings_mode(discord_ipc::types::voice_settings_mode voice_settings_mode) {
			this->voice_settings_mode = voice_settings_mode;
			return *this;
		};
		voice_settings set_automatic_gain_control(bool automatic_gain_control) {
			this->automatic_gain_control = automatic_gain_control;
			return *this;
		}
		voice_settings set_echo_cancellation(bool echo_cancellation) {
			this->echo_cancellation = echo_cancellation;
			return *this;
		}
		voice_settings set_noise_suppression(bool noise_suppression) {
			this->noise_suppression = noise_suppression;
			return *this;
		}
		voice_settings set_qos(bool qos) {
			this->qos = qos;
			return *this;
		}
		voice_settings set_silence_warning(bool silence_warning) {
			this->silence_warning = silence_warning;
			return *this;
		}
		voice_settings set_deaf(bool deaf) {
			this->deaf = deaf;
			return *this;
		}
		voice_settings set_mute(bool mute) {
			this->mute = mute;
			return *this;
		}
		static voice_settings from_json(std::string json);
		std::string to_json() const;
	};
}