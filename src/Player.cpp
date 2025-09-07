//
// Created by kshitij on 06/09/25.
//

#include "Player.hpp"

#include <limits.h>

Player::Player(const Vector2 pos) {
    position = pos;
}

void Player::GetInputs() {
    horizontal.x = IsKeyDown(KEY_LEFT) ? -1 : IsKeyDown(KEY_RIGHT) ? 1 : 0;

    if (IsKeyPressed(KEY_Z)) {
        _canJump = true;
    }
    if (IsKeyReleased(KEY_Z) && velocity.y < 0) {
        velocity.y = velocity.y * jumpStopFactor;
    }
}

void Player::Jump() {
    velocity.y = jumpHeight;
}

void Player::Update() {
    // Euler's method
    velocity.x = (horizontal.x * speed);
    // Gravity
    velocity += acceleration;

    position += velocity;
    position.y = Clamp(position.y, INT_MIN, 400 - size.y);

    if (_canJump) {
        Jump();
        _canJump = false;
    }
}

void Player::Draw() {
    DrawRectangle(position.x, position.y,size.x, size.y, RED);
}

