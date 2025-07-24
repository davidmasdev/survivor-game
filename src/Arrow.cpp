//
// Created by david on 7/24/2025.
//

#include "Arrow.h"

#include <ctime>

Arrow::Arrow(Vector2 position, Texture2D texture, int direction, int timeToLive) {
    this->position = position;
    this->texture = texture;
    this->direction = direction;
    this->timeToLive = timeToLive;
    this->radius = 3.0f;
    this->speed = 200.0f;
}

Arrow::~Arrow() {
    // UnloadTexture(texture);
}


Vector2 Arrow::getPosition() {
    return this->position;
}

Texture2D Arrow::getTexture() {
    return this->texture;
}

float Arrow::getRadius() {
    return this->radius;
}

float Arrow::getSpeed() {
    return this->speed;
}

int Arrow::getDirection() {
    return this->direction;
}

int Arrow::getTimeToLive() {
    return this->timeToLive;
}

void Arrow::setPositon (Vector2 position) {
    this->position = position;
}

void Arrow::decreaseTimeToLive(float deltaTime) {
    timeToLive -= deltaTime;
}

void Arrow::setTimeToLive(int newTimeToLive) {
    this->timeToLive = newTimeToLive;
}

