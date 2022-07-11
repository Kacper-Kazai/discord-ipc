set(tests ${PROJECT_NAME}-tests)

find_package(GTest REQUIRED)

file(GLOB_RECURSE TESTS_SOURCES
    *.cpp
)

add_executable(${tests} ${TESTS_SOURCES})

target_link_libraries(${tests} 
	PRIVATE
		GTest::GTest
		discord-ipc::lib
		nlohmann_json::nlohmann_json
)

