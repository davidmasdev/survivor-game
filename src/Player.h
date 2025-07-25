//
// Created by david on 7/21/2025.
//
#pragma once

#ifndef PLAYER_H
#include <vector>

#include "Arrow.h"
#include "raylib.h"

class Enemy;

class Player {

private:
    Vector2 position;
    Vector2 velocity;
    float speed;
    float deltaTime;
    Texture2D texture;
    Texture2D arrowTexture;
    float health;
    bool hit;
    float hitCooldown;
    int direction;
    float arrowCooldown;
    float arrowCooldownValue;

    std::vector<Arrow> arrows;

    void move(Vector2 newVelocity);

public:
    Player(float x, float y);
    void handleKeys(std::vector<Enemy> &enemies);
    Vector2 getPosition();
    Vector2 getVelocity();
    Texture2D getTexture();
    float getDeltaTime();
    float getHealth();
    int getDirection();
    void upgradeHealth(float increase);
    void upgradeSpeed(float increase);
    void upgradeCooldown(float increase);
    bool canBeHit();
    void hitPlayer();
    void update(std::vector<Enemy> &enemies);
    void shoot();
    std::vector<Arrow>& getArrows();
};

#define PLAYER_H

#endif //PLAYER_H
