//
// Created by kshitij on 07/09/25.
//

#ifndef PLATFORMER_RL_PLATFORM_HPP
#define PLATFORMER_RL_PLATFORM_HPP
#include <raylib.h>

#include "GameObject.hpp"

class Platform : public GameObject {
public:
    Vector2 size;
    bool isStatic = true;

    Platform(int x, int y, int w, int h);

    void Draw() override;
    void Update(float dt) override;
};

#endif //PLATFORMER_RL_PLATFORM_HPP