//
// Created by kshitij on 07/09/25.
//

#include "World.hpp"

#include <cstdlib>

#include "Constants.hpp"
#include <iostream>
#include <limits.h>

World::World() {
    // Main ground tiles
    srand(time(nullptr));
    platforms.emplace_back(Constants::WIDTH/2 - 20, Constants::HEIGHT, 40, 40);
    // for (int i = 0; i < 20; i++) {
    //     const float r1 = 2 * (rand() * 1.f / INT_MAX) - 1;
    //     const float r2 = 2 * (rand() * 1.f / INT_MAX) - 1;
    //
    //     const int x = r1 * Constants::WIDTH;
    //     const int y = r2 * Constants::HEIGHT;
    //
    //     platforms.push_back(Platform(x, y, 200, 50));
    // }
}

auto World::Draw() -> void {
    // Draw platforms
    for (auto platform: platforms) {
        platform.Draw();
    }
}

auto World::Update(float deltaTime) -> void {
    return;
}

