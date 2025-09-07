//
// Created by kshitij on 07/09/25.
//

#include "World.hpp"

#include <cstdlib>

#include "Constants.hpp"
#include <iostream>
#include <limits.h>

World::World() {
    // Main ground tile
    srand(time(nullptr));
    platforms.push_back(Platform(Constants::WIDTH/2 - 100, Constants::GROUND_HEIGHT, 200, 50));
    for (int i = 0; i < 20; i++) {
        const float r1 = 2 * (rand() * 1.f / INT_MAX) - 1;
        const float r2 = 2 * (rand() * 1.f / INT_MAX) - 1;

        const int x = r1 * Constants::WIDTH;
        const int y = r2 * Constants::HEIGHT;

        platforms.push_back(Platform(x, y, 200, 50));
    }
}

void World::Draw() {
    // Draw platforms
    for (auto platform: platforms) {
        platform.Draw();
    }
}

void World::Update(float deltaTime) {
    return;
}

