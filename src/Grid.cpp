//
// Created by david on 7/21/2025.
//

#include "Grid.h"
#include "raylib.h"

const int CELL_SIZE = 16;

Grid::Grid() {
    Texture2D mapTexture = LoadTexture("../resources/tiles/tilemap.png");

    for (float i=-32; i<32; i++) {
        for (float j=-32; j<32; j++) {
            this->cells.push_back(Cell(mapTexture, Vector2(i*CELL_SIZE, j*CELL_SIZE)));
        }
    }
}


std::vector<Cell> Grid::getCells() {
    return this->cells;
}
