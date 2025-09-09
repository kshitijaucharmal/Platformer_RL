//
// Created by kshitij on 9/9/25.
//

#pragma once

#include <raylib.h>
#include <string>
#include <map>

#include "Player.hpp"
#include "World.hpp"

enum TileType {
    PLAYER = 0,
    PLATFORM = 1
};

class LevelGenerator {
public:
    LevelGenerator();

    unsigned long rgb2hex(int r, int g, int b) {
        return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
    }

    std::map<unsigned long, TileType> mappings;
    int gridSize = 50;

    void GenerateFromImage(std::string imagePath, World* world, Player* player);
};
