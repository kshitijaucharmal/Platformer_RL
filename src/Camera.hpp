//
// Created by kshitij on 07/09/25.
//

#include "raylib.h"

#ifndef PLATFORMER_RL_CAMERA_HPP
#define PLATFORMER_RL_CAMERA_HPP

class CameraManager {
public:
    Camera2D camera;
    Vector2 fixedTarget;
    Vector2 targetSize;

    CameraManager(Vector2 player, Vector2 player_size);

    void Update(Vector2 targetPos);
    void DebugLines();
};

#endif //PLATFORMER_RL_CAMERA_HPP