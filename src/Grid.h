//
// Created by david on 7/21/2025.
//
#pragma once

#ifndef GRID_H
#define GRID_H
#include <vector>

#include "Cell.h"


class Grid {
private:
    std::vector<Cell> cells;
public:
    Grid();
    std::vector<Cell> getCells();
};



#endif //GRID_H
