//
// Created by david on 7/21/2025.
//

#include "Grid.h"

Grid::Grid() {
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            this->cells[i].push_back(Cell());
        }
    }
}


std::vector<std::vector<Cell>> Grid::getCells() {
    return this->cells;
}
