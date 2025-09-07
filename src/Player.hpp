//
// Created by kshitij on 06/09/25.
//
#include "raylib.h"
#include "raymath.h"
#include "World.hpp"

#ifndef PLATFORMER_RL_PLAYER_HPP
#define PLATFORMER_RL_PLAYER_HPP

class Player {
public:
    // Display
    Vector2 size = Vector2(40, 40);

    // Basic
    Vector2 position = {400, 400};
    Vector2 velocity = {0, 0};
    Vector2 acceleration = {0, 9.8f * 5};

    bool isGrounded = false;
    Rectangle collisionShape;

    // Visual
    Texture2D texture;

    // Movement
    Vector2 horizontal;
    float speed = 450;
    float jumpHeight = 18;
    float jumpStopFactor = 0.3f;
    float sprintMultiplier = 1.7f;
    bool _canJump = false;

    Player(Vector2 pos);
    ~Player();

    void GetInputs();
    void Update(float dt);
    void Draw();

    void Jump(float dt);

    void CheckCollisions(const World &world);
};


#endif //PLATFORMER_RL_PLAYER_HPP