//
// Created by david on 7/23/2025.
//
#pragma once

#ifndef ENEMY_H
#define ENEMY_H
#include <vector>

#include "raylib.h"


class Player;

class Enemy {
private:
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    float health;
    float speed;
public:
    Enemy(Vector2 position);
    Vector2 getPosition();
    Texture2D getTexture();
    void moveToPlayer(Player &player, std::vector<Enemy> enemies);
};



#endif //ENEMY_H
