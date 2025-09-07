//
// Created by kshitij on 07/09/25.
//

#include "Platform.hpp"

Platform::Platform(int x, int y, int w, int h) {
    position = Vector2(x, y);
    size = Vector2(w, h);

    collisionShape = Rectangle(x, y, w, h);
}


void Platform::Draw() {
    DrawRectangleRounded(
        Rectangle(position.x, position.y, size.x, size.y),
        0.2,
        5,
        RAYWHITE);
}
