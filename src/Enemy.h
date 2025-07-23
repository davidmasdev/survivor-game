//
// Created by david on 7/23/2025.
//
#pragma once



#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"


class Enemy {
private:
    Vector2 position;
    Texture2D texture;
    int health;
    float speed;
public:
    Enemy(Vector2 position);
    ~Enemy();
    Vector2 getPosition();
    Texture2D getTexture();
};



#endif //ENEMY_H
