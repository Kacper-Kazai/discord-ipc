set(example ${PROJECT_NAME}-example)


find_package(CURL REQUIRED)

add_executable(${example} example.cpp)

target_link_libraries(${example}
	PRIVATE
		discord-ipc::lib
		nlohmann_json::nlohmann_json
		CURL::libcurl
)