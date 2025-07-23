//
// Created by david on 7/21/2025.
//

#include "Player.h"

#include <cmath>
#include <vector>

#include "Enemy.h"

const int CELL_SIZE = 16;


Player::Player(float x, float y) {
    this->position = { x , y };
    this->velocity = { 0 , 0};
    this->speed = 200.0f;
    this->deltaTime = 0.016f;

    const Texture2D initTexture = LoadTexture("../resources/textures/entities.png");
    this->texture = initTexture;
}

void Player::handleKeys(std::vector<Enemy> enemies) {
    const float enemyRadius = 6.0f;
    const float playerRadius = 6.0f;

    velocity = Vector2{0, 0};

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) velocity.x+=1;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) velocity.x-=1;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) velocity.y+=1;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) velocity.y-=1;

    float length = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (length > 0) {
        velocity.x /= length;
        velocity.y /= length;
    }


    for (auto& enemy : enemies) {
        int dx = position.x + velocity.x * speed * deltaTime - enemy.getPosition().x;
        int dy = position.y + velocity.y * speed * deltaTime  - enemy.getPosition().y;

        int distance = sqrt(dx * dx + dy * dy);
        if (distance < enemyRadius + playerRadius) {
            return;
        }

    }


    if (position.x + velocity.x * speed * deltaTime < 32 * CELL_SIZE && position.y + velocity.y * speed * deltaTime < 32 * CELL_SIZE &&
        position.x + velocity.x * speed * deltaTime > -32 * CELL_SIZE && position.y + velocity.y * speed * deltaTime > -32 * CELL_SIZE)
    move(velocity);
}

void Player::move(Vector2 newVelocity) {
    position.x += newVelocity.x * speed * deltaTime;
    position.y += newVelocity.y * speed * deltaTime;
}

Vector2 Player::getPosition() {
    return this->position;
}

Vector2 Player::getVelocity() {
    return this->velocity;
}

Texture2D Player::getTexture() {
    return this->texture;
}

float Player::getDeltaTime() {
    return this->deltaTime;
}