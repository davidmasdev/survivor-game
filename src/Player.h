//
// Created by david on 7/21/2025.
//
#pragma once

#ifndef PLAYER_H
#include <vector>

#include "raylib.h"

class Enemy;

class Player {

private:
    Vector2 position;
    Vector2 velocity;
    float speed;
    float deltaTime;
    Texture2D texture;
    float health;
    bool hit;
    float hitCooldown;

    void move(Vector2 newVelocity);

public:
    Player(float x, float y);
    void handleKeys(std::vector<Enemy> enemies);
    Vector2 getPosition();
    Vector2 getVelocity();
    Texture2D getTexture();
    float getDeltaTime();
    float getHealth();
    bool canBeHit();
    void hitPlayer();
    void update();
};

#define PLAYER_H

#endif //PLAYER_H
