//
// Created by kshitij on 07/09/25.
//

#include "Platform.hpp"
#include <vector>

#ifndef PLATFORMER_RL_WORLD_HPP
#define PLATFORMER_RL_WORLD_HPP

class World {
public:
    World();

    std::vector<Platform> platforms;

    void Update(float deltaTime);
    void Draw();
};

#endif //PLATFORMER_RL_WORLD_HPP