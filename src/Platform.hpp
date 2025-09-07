//
// Created by kshitij on 07/09/25.
//

#ifndef PLATFORMER_RL_PLATFORM_HPP
#define PLATFORMER_RL_PLATFORM_HPP
#include <raylib.h>

class Platform {
    public:
    Vector2 position;
    Vector2 size;

    Rectangle collisionShape;

    bool isStatic = true;

    Platform(int x, int y, int w, int h);

    void Draw();
};

#endif //PLATFORMER_RL_PLATFORM_HPP