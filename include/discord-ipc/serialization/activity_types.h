#pragma once
namespace discord_ipc::types {
	enum class activity_types {
		game = 0,
		streaming = 1,
		listening = 2,
		watching = 3,
		custom = 4,
		competing = 5
	};
}