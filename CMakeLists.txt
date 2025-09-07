cmake_minimum_required(VERSION 3.48)
project(Platformer_RL)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp
        src/Player.cpp
        src/Player.hpp)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
