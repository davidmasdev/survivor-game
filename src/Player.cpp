//
// Created by david on 7/21/2025.
//

#include "Player.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

#include "Arrow.h"
#include "Enemy.h"

const int CELL_SIZE = 16;

Player::Player(float x, float y) {
    this->position = { x , y };
    this->velocity = { 0 , 0};
    this->speed = 100.0f;
    this->deltaTime = 0.016f;
    this->health = 3.0f;
    this->hit = false;
    this->arrowCooldown = 0.0f;


    const Texture2D initTexture = LoadTexture("../resources/textures/entities.png");
    this->texture = initTexture;

    const Texture2D initArrowTexture = LoadTexture("../resources/textures/arrows.png");
    this->arrowTexture = initArrowTexture;
}

void Player::handleKeys(std::vector<Enemy> enemies) {
    const float enemyRadius = 6.0f;
    const float playerRadius = 6.0f;

    velocity = Vector2{0, 0};

    if (IsKeyDown(KEY_SPACE) && arrowCooldown <= 0) shoot();

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) { velocity.x+=1; direction =0; }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) { velocity.x-=1; direction = 180; }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) { velocity.y+=1; direction = 90; }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) { velocity.y-=1; direction = 270; }

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

float Player::getHealth() {
    return this->health;
}

bool Player::canBeHit() {
    return this->hitCooldown <= 0;
}

void Player::hitPlayer() {
    if (!canBeHit()) {
        return;
    }

    this->hit = true;
    this->hitCooldown = 0.4f;
    this->health--;
}

void Player::update() {
    if (hitCooldown > 0) {
        hitCooldown -= deltaTime;
    }

    if (arrowCooldown > 0) {
        arrowCooldown -= deltaTime;
    }

    for (auto& arrow : arrows) {
        if (arrow.getTimeToLive()>0) {
            Vector2 velocity = {0, 0};
            switch (arrow.getDirection()) {
                case 0:
                    velocity.x++;
                    break;
                case 180:
                    velocity.x--;
                    break;
                case 90:
                    velocity.y++;
                    break;
                case 270:
                    velocity.y--;
                    break;
            }
            Vector2 currentPos = arrow.getPosition();
            Vector2 newPosition = {
                currentPos.x + velocity.x * arrow.getSpeed() * deltaTime,
                currentPos.y + velocity.y * arrow.getSpeed() * deltaTime
            };
            arrow.setPositon(newPosition);
            arrow.decreaseTimeToLive(deltaTime);
        }
    }

    arrows.erase(
        std::remove_if(arrows.begin(), arrows.end(),
            [](Arrow& arrow) {
                return arrow.getTimeToLive() <= 0;
            }),
        arrows.end()
    );
}

void Player::shoot() {
    Vector2 arrowPosition = position;
    switch (direction) {
        case 0:
            arrowPosition.x+=16;
            break;
        case 180:
            arrowPosition.x-=8;
            arrowPosition.y+=16;
            break;
        case 90:
            arrowPosition.y+=16;
            arrowPosition.x+=16;
            break;
        case 270:
            arrowPosition.y-=8;
            break;
    }
    arrows.push_back(Arrow(arrowPosition, arrowTexture, this->direction, 5*16));
    arrowCooldown = 0.5f;
}

std::vector<Arrow> Player::getArrows() {
    return this->arrows;
}

int Player::getDirection() {
    return this->direction;
}
