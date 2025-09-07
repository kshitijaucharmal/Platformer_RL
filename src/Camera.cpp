//
// Created by kshitij on 07/09/25.
//

#include "Camera.hpp"

#include <iostream>
#include <ostream>
#include <raymath.h>

#include "Constants.hpp"

CameraManager::CameraManager(Vector2 player, Vector2 player_size) {
    camera = { 0 };
    fixedTarget = player;
    targetSize = player_size;
    camera.target = player + targetSize/2;
    camera.offset = (Vector2){ Constants::WIDTH/2.0f, Constants::HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void CameraManager::Update(Vector2 targetPos) {
    fixedTarget = targetPos + targetSize/2;
    camera.target = Vector2Lerp(camera.target, targetPos + targetSize/2, 0.08f);
}

void CameraManager::DebugLines() {
    // DrawLine(fixedTarget.x + targetSize.x, -Constants::HEIGHT, fixedTarget.x + targetSize.x, Constants::HEIGHT, GREEN);
    // DrawLine(-Constants::WIDTH*10, fixedTarget.y, Constants::WIDTH*10, fixedTarget.y, GREEN);
    // DrawRectangle(camera.target.x - Constants::WIDTH/2 - 10, camera.target.y - Constants::HEIGHT/2-10, Constants::WIDTH-20, Constants::HEIGHT-20, ColorAlpha(SKYBLUE, 0.3));
    // DrawRectangle(camera.target.x - 2, camera.target.y - 2, 4, 4, YELLOW);
}
