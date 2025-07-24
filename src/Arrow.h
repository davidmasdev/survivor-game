//
// Created by david on 7/24/2025.
//
# pragma once


#ifndef ARROW_H
#define ARROW_H
#include "raylib.h"


class Arrow {
private:
    Vector2 position;
    Texture2D texture;
    float speed;
    float radius;
    bool hit;
    int direction;
    int timeToLive;
public:
    Arrow(Vector2 position, Texture2D texture, int direction, int timeToLive);
    ~Arrow();
    Vector2 getPosition();
    Texture2D getTexture();
    float getRadius();
    float getSpeed();
    int getDirection();
    int getTimeToLive();
    void setTimeToLive(int newTimeToLive);
    void setPositon (Vector2 position);
    void decreaseTimeToLive(float deltaTime);
    // bool hit;
};



#endif //ARROW_H
