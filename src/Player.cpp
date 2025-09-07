//
// Created by kshitij on 06/09/25.
//

#include "Player.hpp"
#include "World.hpp"

Player::Player(Vector2 pos) {
    pos -= size/2;
    position = pos;

    collisionShape = Rectangle(pos.x, pos.y, size.x, size.y);

    Image image = LoadImage(ASSET_DIR "/player/idle0.png");
    ImageResize(&image, size.x, size.y);
    // Load textures
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

void Player::GetInputs() {
    horizontal.x = IsKeyDown(KEY_LEFT) ? -1 : IsKeyDown(KEY_RIGHT) ? 1 : 0;

    if (isGrounded && IsKeyPressed(KEY_Z)) {
        _canJump = true;
    }
    if (IsKeyReleased(KEY_Z) && velocity.y < 0) {
        velocity.y = velocity.y * jumpStopFactor;
    }
}

void Player::Jump(float dt) {
    velocity.y = -jumpHeight;
}

void Player::CheckCollisions(const World &world) {
    for (const auto platform : world.platforms) {
        if (CheckCollisionRecs(platform.collisionShape, collisionShape)){
            const float prevBottom = position.y - velocity.y + size.y;

            // Only resolve if falling onto the platform
            if (prevBottom <= platform.position.y) {
                position.y = platform.position.y - size.y;
                velocity.y = 0;
                isGrounded = true;
            }
        }
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

    if (_canJump) {
        Jump(dt);
        _canJump = false;
        isGrounded = false;
    }
}

void Player::Draw() {
    // DrawRectangleRounded(
    //     Rectangle{ position.x, position.y,size.x, size.y},
    //     0.2,
    //     10,
    //     RED);

    DrawTexture(texture, position.x, position.y, WHITE);
}

Player::~Player() {
    UnloadTexture(texture);
}
