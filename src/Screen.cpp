//
// Created by david on 7/21/2025.
//

#include "Screen.h"

#include <string>

#include "raylib.h"

Screen::Screen(int width, int height) {
    this->width = width;
    this->height = height;
}


void Screen::draw(Player player) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    std::string initialMessage = "Welcome to the Survivor Game";
    DrawText(initialMessage.c_str(), (this->width/2)-MeasureText(initialMessage.c_str(), 20)/2, 10, 20, LIGHTGRAY);

    Vector2 playerPos = player.getPosition();
    DrawCircle(playerPos.x, playerPos.y, 25, RED);

    EndDrawing();
}
