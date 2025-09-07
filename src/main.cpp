#include <complex>
#include <vector>

#include "Camera.hpp"
#include "Constants.hpp"
#include "Platform.hpp"
#include "raylib.h"
#include "Player.hpp"
#include "World.hpp"

// NOTE: Gamepad name ID depends on drivers and OS
#define XBOX_ALIAS_1 "xbox"

// Constants
int gamepad = 2; // which gamepad to display

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Set MSAA 4X hint before windows creation
    InitWindow(Constants::WIDTH, Constants::HEIGHT, "Platformer");
    SetTargetFPS(75);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    World world;

    // GameObjects init
    Player player(Vector2(Constants::WIDTH/2, Constants::HEIGHT/5));
    CameraManager camera_manager(player.position, player.size);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime();
        // Update
        //----------------------------------------------------------------------------------
        player.GetInputs();
        player.CheckCollisions(world);

        world.Update(dt);
        player.Update(dt);

        camera_manager.Update(player.position);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera_manager.camera);
                world.Draw();
                player.Draw();
                camera_manager.DebugLines();

            EndMode2D();

            DrawText(player.isGrounded ? "TRUE" : "FALSE", 200, 30, 18, BLACK);

            // Debug
            // -----------------------------------------------------------------------------
            DrawFPS(10, 10);
            // -----------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
