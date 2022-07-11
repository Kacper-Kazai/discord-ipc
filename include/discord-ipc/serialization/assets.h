#pragma once
#include <string>
#include <optional>

namespace discord_ipc::types {
	class assets {
		std::optional<std::string> large_image;
		std::optional<std::string> large_text;
		std::optional<std::string> small_image;
		std::optional<std::string> small_text;
	public:
		assets(std::optional<std::string> large_image = std::nullopt, std::optional<std::string> large_text = std::nullopt, std::optional<std::string> small_image = std::nullopt, std::optional<std::string> small_text = std::nullopt) {
			if (large_image) this->large_image = *large_image;
			if (large_text) this->large_text = *large_text;
			if (small_image) this->small_image = *small_image;
			if (small_text) this->small_text = *small_text;
		};
		std::optional<std::string> get_large_image() const {
			return this->large_image;
		};
		std::optional<std::string> get_large_text() const {
			return this->large_text;
		};
		std::optional<std::string> get_small_image() const {
			return this->small_image;
		};
		std::optional<std::string> get_small_text() const {
			return this->small_text;
		};
		assets& set_large_image(std::string large_image) {
			this->large_image = large_image;
			return *this;
		}
		assets& set_large_text(std::string large_text) {
			this->large_text = large_text;
			return *this;
		}
		assets& set_small_image(std::string small_image) {
			this->small_image = small_image;
			return *this;
		}
		assets& set_small_text(std::string small_text) {
			this->small_text = small_text;
			return *this;
		}
		static assets from_json(std::string json);
		std::string to_json() const;
	};
}