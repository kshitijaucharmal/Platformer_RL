#include <complex>
#include <vector>

#include "Camera.hpp"
#include "Constants.hpp"
#include "LevelGenerator.hpp"
#include "raylib.h"
#include "Player.hpp"

#include "imgui.h"
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


    lvlGen.GenerateFromImage(ASSET_DIR "/levels/map1.png", &world, &player);
    bool open = true;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime();
        // Update
        //----------------------------------------------------------------------------------
        player.GetInputs();

        world.Update(dt);
        player.Update(dt);

        player.CheckCollisions(world);

        camera_manager.Update(player.position);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera_manager.camera);
                world.Draw();
                player.Draw();
                camera_manager.DebugLines();

            EndMode2D();

            // Debug
            // -----------------------------------------------------------------------------
            DrawFPS(10, 10);
            // -----------------------------------------------------------------------------

        // start ImGui Conent
        rlImGuiBegin();

        // show ImGui Content
        ImGui::ShowDemoWindow(&open);

        // end ImGui Content
        rlImGuiEnd();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
