//
// Created by kshitij on 07/09/25.
//

#include "World.hpp"

#include <cstdlib>

#include "Constants.hpp"
#include <iostream>
#include <limits.h>

#include "LevelGenerator.hpp"

World::World() {
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

