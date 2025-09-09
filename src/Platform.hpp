//
// Created by kshitij on 07/09/25.
//

#pragma once
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