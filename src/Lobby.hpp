//
// Created by kshitij on 11/9/25.
//

#pragma once
#include <unordered_map>

#include "Camera.hpp"
#include "LevelGenerator.hpp"
#include "NetworkClient.hpp"

class Lobby {
public:
    Lobby(LevelGenerator& lvlGen, World& world, Player& player);

    World& world;
    Player& player;

    bool isReady = false;

    bool IsEveryoneReady();
    void Loop(NetworkClient& networkClient, CameraManager& camera_manager);
};
