//
// Created by kshitij on 9/9/25.
//

#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>

struct TileMap {
    std::unordered_map<int, void*> mappings;
};

class LevelGenerator {
public:
    LevelGenerator();

    void GenerateFromImage(std::string imagePath);
    void LoadMappings();
};
