#pragma once
#include "certified_device_types.h"
#include "vendor.h"
#include "model.h"
#include <string>
#include <optional>
#include <vector>

namespace discord_ipc::types {
	class certified_device {
		certified_device_type type;
		std::string id;
		vendor vendor;
		model model;
		std::vector<std::string> related_array;
		std::optional<bool> echo_cancellation;
		std::optional<bool> noise_suppression;
		std::optional<bool> automatic_gain_control;
		std::optional<bool> hardware_mute;
	public:
		certified_device() {};
		certified_device(certified_device_type type, std::string id, discord_ipc::types::vendor vendor, discord_ipc::types::model model, std::optional<std::vector<std::string>> related_array =std::nullopt) {
			this->type = type;
			this->id = id;
			this->vendor = vendor;
			this->model = model;
			if(related_array) this->related_array = *related_array;
		}
		certified_device_type get_type() const {
			return this->type;
		}
		std::string get_id() {
			return this->id;
		};
		discord_ipc::types::vendor get_vendor() const {
			return this->vendor;
		};
		discord_ipc::types::model get_model() const {
			return this->model;
		};
		std::vector<std::string> get_related() const {
			return this->related_array;
		};
		std::optional<bool> get_echo_cancellation() const {
			return this->echo_cancellation;
		};
		std::optional<bool> get_noise_suppression() const {
			return this->noise_suppression;
		};
		std::optional<bool> get_automatic_gain_control() const {
			return this->automatic_gain_control;
		};
		std::optional<bool> get_hardware_mute() const {
			return this->hardware_mute;
		};
		certified_device& add_related(std::string id) {
			related_array.push_back(id);
			return *this;
		}
		certified_device& remove_related(std::string id) {
			auto related_item = std::find(related_array.begin(), related_array.end(), id);
			if (related_item != related_array.end()) related_array.erase(related_item);
			return *this;
		};
		certified_device& set_echo_cancellation(bool echo_cancellation) {
			this->echo_cancellation = echo_cancellation;
			return *this;
		}
		certified_device& set_noise_suppression(bool noise_suppression) {
			this->noise_suppression = noise_suppression;
			return *this;
		}
		certified_device& set_automatic_gain_control(bool automatic_gain_control) {
			this->automatic_gain_control = automatic_gain_control;
			return *this;
		}
		certified_device& set_hardware_mute(bool hardware_mute) {
			this->hardware_mute = hardware_mute;
			return *this;
		}
		static certified_device from_json(std::string json);
		std::string to_json() const;

		bool operator==(const certified_device& other) const {
			return this->to_json() == other.to_json();
		}
		bool operator!=(const certified_device& other) const {
			return !operator==(other);
		}
	};
}