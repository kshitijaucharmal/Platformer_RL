cmake_minimum_required(VERSION 3.48)
project(Platformer_RL)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib REQUIRED)

file(GLOB_RECURSE SOURCE_FILES src/*)

set(ASSET_PATH "${CMAKE_SOURCE_DIR}/assets")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

target_compile_definitions(${PROJECT_NAME} PRIVATE ASSET_DIR="${ASSET_PATH}")