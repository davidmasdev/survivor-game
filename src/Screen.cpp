//
// Created by david on 7/21/2025.
//

#include "Screen.h"

#include <string>

#include "raylib.h"

Screen::Screen(int width, int height, Player player) {
    this->width = width;
    this->height = height;
    // this->camera = { 0 };
    this->camera.target = player.getPosition();
    this->camera.offset = (Vector2){ width/2.0f, height/2.0f };
    this->camera.rotation = 0.0f;
    this->camera.zoom = 1.0f;
}


void Screen::draw(Player player) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    std::string initialMessage = "Welcome to the Survivor Game";
    DrawText(initialMessage.c_str(), (this->width/2)-MeasureText(initialMessage.c_str(), 20)/2, 10, 20, LIGHTGRAY);

    Vector2 playerPos = player.getPosition();
    float lerp = 0.8f;

    camera.target.x += (playerPos.x - camera.target.x) * lerp * player.getDeltaTime();
    camera.target.y += (playerPos.y - camera.target.y) * lerp * player.getDeltaTime();

    BeginMode2D(camera);

    DrawCircle(playerPos.x, playerPos.y, 25, RED);

    EndMode2D();

    EndDrawing();
}
