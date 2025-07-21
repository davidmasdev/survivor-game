//
// Created by david on 7/21/2025.
//

#include "Player.h"

#include <cmath>

Player::Player(float x, float y) {
    this->position = { x , y };
    this->velocity = { 0 , 0};
    this->speed = 200.0f;
    this->deltaTime = 0.016f;
}

void Player::handleKeys() {
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

    move(velocity);
}

void Player::move(Vector2 newVelocity) {
    position.x += newVelocity.x * speed * deltaTime;
    position.y += newVelocity.y * speed * deltaTime;
}

Vector2 Player::getPosition() {
    return this->position;
}