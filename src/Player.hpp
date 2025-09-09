//
// Created by kshitij on 06/09/25.
//
#include "GameObject.hpp"
#include "raylib.h"
#include "raymath.h"
#include "World.hpp"

#ifndef PLATFORMER_RL_PLAYER_HPP
#define PLATFORMER_RL_PLAYER_HPP

class Player : public GameObject{
public:
    // Display
    Vector2 size = Vector2(40, 40);

    bool isGrounded = false;

    // Visual
    Texture2D texture;

    // Movement
    Vector2 horizontal;
    float speed = 450;
    float jumpHeight = 18;
    float jumpStopFactor = 0.3f;
    float sprintMultiplier = 1.7f;
    bool _canJump = false;

    // Better Platformer
    float hangTime = 0.1f;
    float hangTimeCtr;

    float jumpBufferTime = 0.1f;
    float jumpBufferCounter;

    Player(Vector2 pos);
    ~Player();

    void GetInputs();
    void Update(float dt) override;
    void Draw() override;

    void Jump(float dt);

    void CheckCollisions(const World &world);
};


#endif //PLATFORMER_RL_PLAYER_HPP