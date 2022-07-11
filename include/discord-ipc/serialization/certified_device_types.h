#pragma once
#include "vendor.h"
#include "model.h"
#include <string>
#include <optional>
#include <vector>

namespace discord_ipc::types {
	class certified_device_type {
		std::string value;
	public:
		certified_device_type() {};
		certified_device_type(const char* value) {
			this->value = value;
		}
		std::string get() const {
			return this->value;
		};
	};
	struct certified_device_types {
		inline static const certified_device_type audio_input = "audioinput";
		inline static const certified_device_type audio_output = "audiooutput";
		inline static const certified_device_type video_input = "videoinput";
	};
}