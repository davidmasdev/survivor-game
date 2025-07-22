//
// Created by david on 7/21/2025.
//

#include "Cell.h"

Cell::Cell(Texture2D texture, Vector2 position) {
    this->texture = texture;
    this->position = position;
}

Texture2D Cell::getTexture() {
    return this->texture;
}

Vector2 Cell::getPosition() {
    return this->position;
}

