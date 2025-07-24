//
// Created by david on 7/23/2025.
//

#include "Enemy.h"
#include "Player.h"

#include <cmath>
#include <ranges>
#include <vector>


const float DELTATIME = 0.016f;
const int CELL_SIZE = 16;

Enemy::Enemy(Vector2 position) {
    this->position = position;
    const Texture2D initTexture = LoadTexture("../resources/textures/entities.png");
    this->texture = initTexture;
    this->speed = 120.0f;
    this->health = 2.0f;
}



Vector2 Enemy::getPosition() {
    return this->position;
}

Texture2D Enemy::getTexture() {
    return this->texture;
}

void Enemy::moveToPlayer(Player &player, std::vector<Enemy> enemies) {
    velocity = Vector2{0, 0};
    const float enemyRadius = 6.0f;
    const float playerRadius = 6.0f;

    Vector2 playerPosition = player.getPosition();

    // Calculate direction to player
    Vector2 direction = {playerPosition.x - position.x, playerPosition.y - position.y};

    // Normalize direction
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction.x /= length;
        direction.y /= length;
    }

    velocity = direction;

    // Calculate proposed new position
    Vector2 newPosition = {
        position.x + velocity.x * speed * DELTATIME,
        position.y + velocity.y * speed * DELTATIME
    };

    // Check collision with other enemies
    bool collisionDetected = false;
    Vector2 separationForce = {0, 0};

    for (auto& enemy : enemies) {
        // Skip self-comparison (assuming you pass the current enemy in the vector)
        if (&enemy == this) continue;

        Vector2 enemyPos = enemy.getPosition();
        float dx = newPosition.x - enemyPos.x;
        float dy = newPosition.y - enemyPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        // Check if enemies would overlap (using radius-based collision)
        if (distance < enemyRadius * 2) {
            collisionDetected = true;

            // Add separation force to push enemies apart
            if (distance > 0) {
                separationForce.x += (dx / distance) * 0.5f;
                separationForce.y += (dy / distance) * 0.5f;
            } else {
                // If exactly on top of each other, add random separation
                separationForce.x += (rand() % 2 == 0 ? 1 : -1) * 0.5f;
                separationForce.y += (rand() % 2 == 0 ? 1 : -1) * 0.5f;
            }
        }
    }

    // Check collision with player (stop at player, don't overlap)
    float playerDx = newPosition.x - playerPosition.x;
    float playerDy = newPosition.y - playerPosition.y;
    float playerDistance = std::sqrt(playerDx * playerDx + playerDy * playerDy);

    if (playerDistance < enemyRadius + playerRadius) {
        // Stop movement towards player if too close
        if (player.canBeHit())
            player.hitPlayer();
        return;
    }

    // Apply separation force if collision detected
    if (collisionDetected) {
        // Normalize separation force
        float sepLength = std::sqrt(separationForce.x * separationForce.x + separationForce.y * separationForce.y);
        if (sepLength > 0) {
            separationForce.x /= sepLength;
            separationForce.y /= sepLength;
        }

        // Blend original velocity with separation force
        velocity.x = velocity.x * 0.3f + separationForce.x * 0.7f;
        velocity.y = velocity.y * 0.3f + separationForce.y * 0.7f;

        // Renormalize
        float newLength = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (newLength > 0) {
            velocity.x /= newLength;
            velocity.y /= newLength;
        }

        // Reduce speed when avoiding collisions
        newPosition.x = position.x + velocity.x * speed * DELTATIME * 0.5f;
        newPosition.y = position.y + velocity.y * speed * DELTATIME * 0.5f;
    }

    // Check world boundaries
    if (newPosition.x < -32 * CELL_SIZE || newPosition.x > 32 * CELL_SIZE ||
        newPosition.y < -32 * CELL_SIZE || newPosition.y > 32 * CELL_SIZE) {
        return;
    }

    // Apply movement
    position = newPosition;

}

void Enemy::hitEnemy() {
    this->hitCooldown = 0.4f;
    this->health--;
}

float Enemy::getHitCooldown() {
    return this->hitCooldown;
}

void Enemy::update() {
    if (hitCooldown>0) {
        hitCooldown -= 0.016f;
    }
}

float Enemy::getHealth() {
    return this->health;
}
