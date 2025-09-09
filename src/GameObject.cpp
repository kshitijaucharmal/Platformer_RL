//
// Created by kshitij on 9/9/25.
//

#include "GameObject.hpp"
#include "raymath.h"

void GameObject::Update(float dt) {
    velocity += acceleration;
    position += velocity * dt;
}

void GameObject::Draw() { }