#include <complex>
#include <iostream>
#include <vector>
#include <oneapi/tbb/task_arena.h>

#include "Camera.hpp"
#include "Constants.hpp"
#include "Game.hpp"
#include "LevelGenerator.hpp"
#include "raylib.h"
#include "Player.hpp"

#include "imgui.h"
#include "NetworkClient.hpp"
#include "rlImGui.h"

// NOTE: Gamepad name ID depends on drivers and OS
#define XBOX_ALIAS_1 "xbox"

// Constants
int gamepad = 2; // which gamepad to display

// Networking
#define PORT 8080

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(Constants::WIDTH, Constants::HEIGHT, "Platformer");
    SetTargetFPS(75);               // Set our game to run at 60 frames-per-second

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    auto io = ImGui::GetIO();

    // Config Flags
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform

    rlImGuiSetup(false);
    //--------------------------------------------------------------------------------------

    // GameObjects init
    LevelGenerator lvlGen;
    World world;

    Player player(Vector2(Constants::WIDTH/2, Constants::HEIGHT/5));
    CameraManager camera_manager(player.position, player.size);

    lvlGen.GenerateFromImage(ASSET_DIR "/levels/lobby.png", &world, &player);

    NetworkClient networkClient;
    ENetPeer* peer = networkClient.ConnectToServerUI(&player);

    Game mainGame(lvlGen, world, player);
    mainGame.Loop(networkClient, camera_manager);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    networkClient.Disconnect();

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
