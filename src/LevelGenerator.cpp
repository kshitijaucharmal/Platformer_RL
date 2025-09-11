//
// Created by kshitij on 9/9/25.
//

#include "LevelGenerator.hpp"

#include <iostream>
#include <utility>

#include "Platform.hpp"
#include "Player.hpp"
#include "World.hpp"
#include <random>

LevelGenerator::LevelGenerator() {
    // Setup mappings
    mappings[rgb2hex(255, 255, 255)] = TileType::PLATFORM;
    mappings[rgb2hex(0, 0, 0)] = TileType::PLATFORM;
    mappings[rgb2hex(255, 0, 0)] = TileType::PLAYER;
}

std::vector<Vector2> LevelGenerator::GetPlayerPositionsFromMap(const std::string imagePath) {
    std::vector<Vector2> possiblePlayerPositions;

    const auto mapImage = LoadImage(imagePath.c_str());
    for (int x = 0 ; x < mapImage.width ; x++) {
        for (int y = 0 ; y < mapImage.height ; y++) {
            auto col = GetImageColor(mapImage, x, y);
            if (col.a == 0) continue;

            auto hex = rgb2hex(col.r, col.g, col.b);
            if (!mappings.contains(hex)) continue;

            auto tt = mappings[hex];

            if (tt == TileType::PLAYER)
                possiblePlayerPositions.emplace_back(x * gridSize, y * gridSize);
        }
    }

    if (possiblePlayerPositions.empty()) {
        std::cout << "Map does not have valid player positions\n" << std::endl;
    }

    return possiblePlayerPositions;
}

void LevelGenerator::GenerateFromImage(const std::string imagePath, World* world) {
    // Clear previous maps
    world->platforms.clear();

    srand(time(nullptr));
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
                    possiblePlayerPositions.emplace_back(x * gridSize, y * gridSize);
                    break;
                default:
                    break;
            }
        }
    }
    // Set Player position
    if (possiblePlayerPositions.empty()) {
        std::cout << "Player position not defined !!" << std::endl;
    }
}

void LevelGenerator::SetPlayerPosition(Player& player) {
    int r = rand() % (possiblePlayerPositions.size());
    player.position = possiblePlayerPositions[r];
}