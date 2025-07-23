//
// Created by david on 7/23/2025.
//
#pragma once



#ifndef ENEMY_H
#define ENEMY_H
#include "Player.h"
#include "raylib.h"


class Enemy {
private:
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    int health;
    float speed;
public:
    Enemy(Vector2 position);
    Vector2 getPosition();
    Texture2D getTexture();
    void moveToPlayer(Vector2 playerPosition);
};



#endif //ENEMY_H
