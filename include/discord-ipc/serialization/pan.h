#pragma once
#include <string>

namespace discord_ipc::types {
	class pan {
		float left{1};
		float right{1};
	public:
		pan() {};
		pan(float left, float right) {
			this->left = left;
			this->right = right;
		}
		float get_left() const {
			return this->left;
		}
		float get_right() const {
			return this->right;
		}
		pan set_left(float left) {
			this->left = left;
			return *this;
		}
		pan set_right(float right) {
			this->right = right;
			return *this;
		}
		static pan from_json(std::string json);
		std::string to_json() const;
	};
}