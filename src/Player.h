//
// Created by david on 7/21/2025.
//
#pragma once

#ifndef PLAYER_H
#include "Enemy.h"
#include "raylib.h"

class Player {

private:
    Vector2 position;
    Vector2 velocity;
    float speed;
    float deltaTime;
    Texture2D texture;

    void move(Vector2 newVelocity);

public:
    Player(float x, float y);
    void handleKeys(std::vector<Enemy> enemies);
    Vector2 getPosition();
    Vector2 getVelocity();
    Texture2D getTexture();
    float getDeltaTime();
};

#define PLAYER_H

#endif //PLAYER_H
