//
// Created by kshitij on 11/9/25.
//

#include "Game.hpp"

#include "imgui.h"
#include "rlImGui.h"

Game::Game(LevelGenerator &lvlGen, World &world, Player &player) : lvlGen(lvlGen), world(world), player(player) {

    // Generate main map (TODO: Will be in loop and random maps later)
    lvlGen.GenerateFromImage(ASSET_DIR "/levels/map1.png", &world, &player);
}

int Game::Loop(NetworkClient& networkClient, CameraManager &camera_manager) {
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
        networkClient.SendPacket(player.username + "|X: " + std::to_string(player.position.x) + " Y: " + std::to_string(player.position.y));

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

        // start ImGui HUD
        rlImGuiBegin();

        // end ImGui Content
        rlImGuiEnd();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

}