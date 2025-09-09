//
// Created by kshitij on 06/09/25.
//

#include "Player.hpp"

#include <string>

#include "World.hpp"
#include <algorithm>

Player::Player(Vector2 pos) {
    pos -= size/2;
    position = pos;

    jumpBufferCounter = 0;
    hangTimeCtr = 0;

    velocity = Vector2{0, 0};
    acceleration = Vector2{0, 9.8f * 5};

    collisionShape = Rectangle(pos.x, pos.y, size.x, size.y);
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

    Rectangle prevCollisionShape = {
        position.x - velocity.x,
        position.y - velocity.y,
        size.x,
        size.y
    };

    for (const auto &platform : world.platforms) {
        if (CheckCollisionRecs(platform.collisionShape, collisionShape)) {
            colliding = true;

            float overlapLeft   = (collisionShape.x + collisionShape.width) - platform.collisionShape.x;
            float overlapRight  = (platform.collisionShape.x + platform.collisionShape.width) - collisionShape.x;
            float overlapTop    = (collisionShape.y + collisionShape.height) - platform.collisionShape.y;
            float overlapBottom = (platform.collisionShape.y + platform.collisionShape.height) - collisionShape.y;

            // Find smallest overlap → that’s the direction of resolution
            float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

            if (minOverlap == overlapTop && prevCollisionShape.y + prevCollisionShape.height <= platform.collisionShape.y) {
                // Landed on top
                position.y = platform.position.y - size.y;
                velocity.y = 0;
                isGrounded = true;
            }
            else if (minOverlap == overlapBottom && prevCollisionShape.y >= platform.collisionShape.y + platform.collisionShape.height) {
                // Hit from below
                position.y = platform.position.y + platform.size.y;
                velocity.y = 0; // maybe bounce or stop
            }
            else if (minOverlap == overlapLeft && prevCollisionShape.x + prevCollisionShape.width <= platform.collisionShape.x) {
                // Hit from left
                position.x = platform.position.x - size.x;
                velocity.x = 0;
            }
            else if (minOverlap == overlapRight && prevCollisionShape.x >= platform.collisionShape.x + platform.size.x) {
                // Hit from right
                position.x = platform.position.x + platform.size.x;
                velocity.x = 0;
            }
        }
    }

    if (!colliding) {
        isGrounded = false;
    }
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
}

Player::~Player() {
    UnloadTexture(texture);
}
