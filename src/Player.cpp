//
// Created by kshitij on 06/09/25.
//

#include "Player.hpp"

#include <string>

#include "World.hpp"

Player::Player(Vector2 pos) {
    pos -= size/2;
    position = pos;

    position = {400, 400};
    velocity = {0, 0};
    acceleration = {0, 9.8f * 5};

    collisionShape = Rectangle(pos.x, pos.y, size.x, size.y);

    // Image image = LoadImage(ASSET_DIR "/player/idle0.png");
    // ImageResize(&image, size.x, size.y);
    // // Load textures
    // texture = LoadTextureFromImage(image);
    // UnloadImage(image);
}

void Player::GetInputs() {
    horizontal.x = IsKeyDown(KEY_LEFT) ? -1 : IsKeyDown(KEY_RIGHT) ? 1 : 0;

    if (IsKeyReleased(KEY_Z) && velocity.y < 0) {
        velocity.y = velocity.y * jumpStopFactor;
    }
}

void Player::Jump(float dt) {
    velocity.y = -jumpHeight;
}

void Player::CheckCollisions(const World &world) {
    bool colliding = false;
    for (const auto platform : world.platforms) {
        if (CheckCollisionRecs(platform.collisionShape, collisionShape)){
            colliding = true;
            const float prevBottom = position.y - velocity.y + size.y;

            // Only resolve if falling onto the platform
            if (prevBottom <= platform.position.y) {
                position.y = platform.position.y - size.y;
                velocity.y = 0;
                isGrounded = true;
            }
        }
    }
    if (!colliding) isGrounded = false;
}

void Player::Update(float dt) {
    velocity.x = (horizontal.x * speed * dt);
    // Gravity
    velocity += acceleration * dt;

    position += velocity;
    // Simple Ground

    collisionShape.x = position.x;
    collisionShape.y = position.y;

    // Coyote time
    if (isGrounded) hangTimeCtr = hangTime;
    else hangTimeCtr -= dt;

    if (IsKeyPressed(KEY_Z)) jumpBufferCounter = jumpBufferTime;
    else jumpBufferCounter -= dt;

    if (jumpBufferCounter >= 0 && hangTimeCtr > 0) {
        _canJump = true;
        jumpBufferCounter = 0;
    }

    if (_canJump) {
        Jump(dt);
        _canJump = false;
        isGrounded = false;
    }
}

void Player::Draw() {
    DrawRectangleRounded(
        Rectangle{ position.x, position.y,size.x, size.y},
        0.2,
        10,
        BLACK);
    DrawRectangleRounded(
        Rectangle{ position.x + 2, position.y + 2,size.x - 4, size.y - 4},
        0.2,
        10,
        RED);

    // DrawTexture(texture, position.x, position.y, WHITE);
}

Player::~Player() {
    UnloadTexture(texture);
}
