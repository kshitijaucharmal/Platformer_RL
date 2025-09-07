//
// Created by kshitij on 06/09/25.
//
#include "raylib.h"
#include "raymath.h"

#ifndef PLATFORMER_RL_PLAYER_HPP
#define PLATFORMER_RL_PLAYER_HPP

class Player {
public:
    // Display
    Vector2 size = Vector2(40, 40);

    // Basic
    Vector2 position = {400, 400};
    Vector2 velocity = {0, 0};
    Vector2 acceleration = {0, 0.98f};

    // Movement
    Vector2 horizontal;
    float speed = 4;
    float jumpHeight = -20;
    float jumpStopFactor = 0.3f;
    float sprintMultiplier = 1.7f;
    bool _canJump = false;

    Player(Vector2 pos);

    void GetInputs();
    void Update();
    void Draw();

    void Jump();
};


#endif //PLATFORMER_RL_PLAYER_HPP