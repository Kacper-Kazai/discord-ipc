#pragma once
#include "activity_flag.h"

namespace discord_ipc::types {
	class activity_flags {
		int flag{};
	public:
		activity_flags() {};
		activity_flags(int flag) {
			this->flag = flag;
		}
		activity_flags(activity_flag activity_flag) : activity_flags(activity_flag.get()) {};
		int get() const {
			return flag;
		}
		bool has(int flag) const {
			return (this->flag & flag) == flag;
		}
		bool has(activity_flag activity_flag) const {
			return this->has(activity_flag.get());
		}
		activity_flags& add(int flag) {
			this->flag |= flag;
			return *this;
		}
		activity_flags& add(activity_flag activity_flag) {
			return this->add(activity_flag.get());
		}
		activity_flags& remove(int flag) {
			this->flag &= ~(flag);
			return *this;
		}
		activity_flags& remove(activity_flag activity_flag) {
			return this->remove(activity_flag.get());
		}
		inline static const activity_flag none = 0;
		inline static const activity_flag instance = 1 << 0;
		inline static const activity_flag join = 1 << 1;
		inline static const activity_flag spectate = 1 << 2;
		inline static const activity_flag join_request = 1 << 3;
		inline static const activity_flag sync = 1 << 4;
		inline static const activity_flag play = 1 << 5;
		inline static const activity_flag party_privacy_friends = 1 << 6;
		inline static const activity_flag party_privacy_voice_channel = 1 << 7;
		inline static const activity_flag embedded = 1 << 8;
	};
}