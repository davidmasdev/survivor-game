//
// Created by david on 7/21/2025.
//

# pragma once


#ifndef SCREEN_H
#define SCREEN_H
#include "Player.h"


class Screen {
private:
    int width;
    int height;
    Camera2D camera;
public:
    Screen(int width, int height, Player player);
    void draw(Player player);
};



#endif //SCREEN_H
