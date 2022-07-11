#pragma once
#include "activity.h"
#include <string>
#include <optional>
#include <vector>
namespace discord_ipc::types {
	class action {
		int pid;
		discord_ipc::types::activity activity;
	public:
		action() {};
		action(int pid, discord_ipc::types::activity activity) {
			this->pid = pid;
			this->activity = activity;
		}
		int get_pid() const {
			return this->pid;
		}
		discord_ipc::types::activity get_activity() const {
			return this->activity;
		}
		static action from_json(std::string json);
		std::string to_json() const;
	};
}