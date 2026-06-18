cmake_minimum_required(VERSION 3.20)
project(Platformer_RL CXX)
set(CMAKE_CXX_STANDARD 20)

# Global Asset Path Definition
set(ASSET_PATH "${CMAKE_SOURCE_DIR}/assets")
file(GLOB_RECURSE SOURCE_FILES src/*)
file(GLOB_RECURSE SERVER_FILES server/*)

# ==============================================================================
# 1. DESKTOP BUILD (When NOT compiling with Emscripten)
# ==============================================================================
if(NOT EMSCRIPTEN)
    add_subdirectory(external/raylib)
    add_subdirectory(external/enet)

    # --- Server ---
    add_executable(server ${SERVER_FILES})
    target_include_directories(server PRIVATE "${CMAKE_SOURCE_DIR}/external/raylib/src")
    target_link_libraries(server PRIVATE enet raylib)

    # --- ImGui ---
    add_library(imgui STATIC
        external/imgui/imgui.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imgui_demo.cpp
    )
    target_include_directories(imgui PUBLIC external/imgui)

    # --- Client ---
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
    target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/external/raylib/src")
    target_compile_definitions(${PROJECT_NAME} PRIVATE ASSET_DIR="${ASSET_PATH}")
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib imgui enet)

# ==============================================================================
# 2. WEB BUILD (When compiling with emcmake cmake)
# ==============================================================================
else()
    # enet must be compiled by Emscripten, so add_subdirectory it here too
    add_subdirectory(external/enet)

    # --- ImGui ---
    add_library(imgui STATIC
        external/imgui/imgui.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imgui_demo.cpp
    )
    target_include_directories(imgui PUBLIC external/imgui)
    target_compile_options(imgui PRIVATE -O3)

    # --- Client ---
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

    target_compile_definitions(${PROJECT_NAME} PRIVATE ASSET_DIR="assets/")

    target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/external/raylib/src"
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/external/enet/include"
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/external/raylib/src/web/libraylib.web.a"
        imgui
        enet      # <-- enet compiled by emcc, linked into the .html/.wasm
    )

    target_compile_options(${PROJECT_NAME} PRIVATE -O3)
    target_link_options(${PROJECT_NAME} PRIVATE
        "-O3"
        "-sUSE_GLFW=3"
        "-sWASM=1"
        "-sASSERTIONS=2"
        "-sASYNCIFY"
        "--preload-file" "${ASSET_PATH}@assets"
    )
endif()
