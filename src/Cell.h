//
// Created by david on 7/21/2025.
//
#pragma once

#ifndef CELL_H
#define CELL_H
#include "raylib.h"


class Cell {
private:
    Texture2D texture;
    Vector2 position;

public:
    Cell(Texture2D texture, Vector2 position);
    Texture2D getTexture();
    Vector2 getPosition();
};



#endif //CELL_H
