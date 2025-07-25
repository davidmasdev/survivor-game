//
// Created by david on 7/21/2025.
//

# pragma once


#ifndef SCREEN_H
#define SCREEN_H
#include "Enemy.h"
#include "Grid.h"
#include "Player.h"


class Screen {
private:
    int width;
    int height;
    Camera2D camera;
public:
    Screen(int width, int height, Player player);
    void draw(Player &player, Grid grid, std::vector<Enemy> &enemies, int waveNum);
};



#endif //SCREEN_H
