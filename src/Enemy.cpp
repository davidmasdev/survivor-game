//
// Created by david on 7/23/2025.
//

#include "Enemy.h"

#include <ranges>

Enemy::Enemy(Vector2 position) {
    this->position = position;
    const Texture2D initTexture = LoadTexture("../resources/textures/entities.png");
    this->texture = initTexture;
    this->speed = 120.0f;
    this->health = 3;
}

Enemy::~Enemy() {

}


Vector2 Enemy::getPosition() {
    return this->position;
}

Texture2D Enemy::getTexture() {
    return this->texture;
}