//
// Created by david on 7/23/2025.
//

#include "Enemy.h"

#include <cmath>
#include <ranges>

const float DELTATIME = 0.016f;
const int CELL_SIZE = 16;

Enemy::Enemy(Vector2 position) {
    this->position = position;
    const Texture2D initTexture = LoadTexture("../resources/textures/entities.png");
    this->texture = initTexture;
    this->speed = 120.0f;
    this->health = 3;
}



Vector2 Enemy::getPosition() {
    return this->position;
}

Texture2D Enemy::getTexture() {
    return this->texture;
}

void Enemy::moveToPlayer(Vector2 playerPosition) {
    velocity = Vector2{0, 0};

    if (position.x - playerPosition.x < 0) velocity.x+=1;
    if (position.x - playerPosition.x > 0) velocity.x-=1;
    if (position.y - playerPosition.y < 0) velocity.y+=1;
    if (position.y - playerPosition.y > 0) velocity.y-=1;


    float length = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (length > 0) {
        velocity.x /= length;
        velocity.y /= length;
    }
    if (position.x + velocity.x * speed * DELTATIME < 32 * CELL_SIZE && position.y + velocity.y * speed * DELTATIME < 32 * CELL_SIZE &&
        position.x + velocity.x * speed * DELTATIME > -32 * CELL_SIZE && position.y + velocity.y * speed * DELTATIME > -32 * CELL_SIZE) {
        position.x += velocity.x * speed * DELTATIME;
        position.y += velocity.y * speed * DELTATIME;
    }

}
