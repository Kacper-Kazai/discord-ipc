cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(discord-ipc VERSION 0.1.0)

option(DISCORD-IPC_WITH_TESTS "Run discord-ipc tests." OFF)
option(DISCORD-IPC_WITH_EXAMPLE "Compile discord-ipc example." OFF)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)
add_library(${PROJECT_NAME} ${SOURCES})
add_library(discord-ipc::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(deps/json)
set(UUID_SYSTEM_GENERATOR ON CACHE INTERNAL "")
add_subdirectory(deps/uuid)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        nlohmann_json::nlohmann_json
        stduuid
)

if(DISCORD-IPC_WITH_TESTS)
    add_subdirectory(tests)
endif()
if(DISCORD-IPC_WITH_EXAMPLE)
    add_subdirectory(example)
endif() 