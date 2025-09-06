#include "raylib.h"

// NOTE: Gamepad name ID depends on drivers and OS
#define XBOX_ALIAS_1 "xbox"

// Constants
constexpr unsigned int WIDTH = 800;
constexpr unsigned int HEIGHT = 450;
int gamepad = 1; // which gamepad to display

// Set axis deadzones
constexpr float leftStickDeadzoneX = 0.1f;
constexpr float leftStickDeadzoneY = 0.1f;
constexpr float rightStickDeadzoneX = 0.1f;
constexpr float rightStickDeadzoneY = 0.1f;
constexpr float leftTriggerDeadzone = -0.9f;
constexpr float rightTriggerDeadzone = -0.9f;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Set MSAA 4X hint before windows creation
    InitWindow(WIDTH, HEIGHT, "Platformer");
    SetTargetFPS(75);               // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // ...
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Some Testing
            // -----------------------------------------------------------------------------
            DrawRectangle(200, 200, 40, 40, BLACK);
            // -----------------------------------------------------------------------------


            // Gamepad stuff ---------------------------------------------------------------
            if (IsGamepadAvailable(gamepad))
            {
                // Draw buttons: Keys
                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) DrawCircle(501, 151, 15, BLUE);
                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) DrawCircle(536, 187, 15, GREEN);
                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) DrawCircle(572, 151, 15, RED);
                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP)) DrawCircle(536, 115, 15, YELLOW);
            }
            else
            {
                DrawText(TextFormat("GP%d: NOT DETECTED", gamepad), 10, 10, 10, GRAY);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
