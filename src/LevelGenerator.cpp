//
// Created by kshitij on 9/9/25.
//

#include "LevelGenerator.hpp"

#include <iostream>

#include "Platform.hpp"
#include "Player.hpp"
#include "World.hpp"


LevelGenerator::LevelGenerator() {
    // Setup mappings
    mappings[rgb2hex(255, 255, 255)] = TileType::PLATFORM;
    mappings[rgb2hex(0, 0, 0)] = TileType::PLATFORM;
    mappings[rgb2hex(255, 0, 0)] = TileType::PLAYER;
}

void LevelGenerator::GenerateFromImage(const std::string imagePath, World* world, Player* player) {
    const auto mapImage = LoadImage(imagePath.c_str());
    for (int x = 0 ; x < mapImage.width ; x++) {
        for (int y = 0 ; y < mapImage.height ; y++) {
            auto col = GetImageColor(mapImage, x, y);
            if (col.a == 0) continue;

            auto hex = rgb2hex(col.r, col.g, col.b);
            if (!mappings.contains(hex)) continue;

            auto tt = mappings[hex];

            switch (tt) {
                case TileType::PLATFORM:
                    world->platforms.emplace_back(x * gridSize, y * gridSize, gridSize, gridSize);
                    break;
                case TileType::PLAYER:
                    player->position.x = x * gridSize;
                    player->position.y = y * gridSize;
                    break;
                default:
                    break;
            }
        }
    }
}