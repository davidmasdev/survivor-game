//
// Created by david on 7/21/2025.
//

#include "Screen.h"

#include <format>
#include <iostream>
#include <string>

#include "raylib.h"
#include "raymath.h"

const int CELL_SIZE = 16;
const float PLAYER_RADIUS = 16.0f;
const float UI_FONT_SIZE = 20.0f;

Screen::Screen(int width, int height, Player player) {
    this->width = width;
    this->height = height;
    this->camera.target = player.getPosition();
    this->camera.offset = (Vector2){ width/2.0f, height/2.0f };
    this->camera.rotation = 0.0f;
    this->camera.zoom = 1.0f;
}

void Screen::draw(Player player, Grid grid) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Camera target player smoothly with bounds
    Vector2 playerPos = player.getPosition();

    // Adjust camera speed based on zoom level
    float baseLerp = 0.9f;
    // float lerp = baseLerp * camera.zoom; // Linear scaling with zoom

    // Alternative approaches:
    float lerp = baseLerp * std::sqrt(camera.zoom); // Square root scaling (more gradual)
    // float lerp = std::min(baseLerp * camera.zoom, 0.98f); // With maximum cap
    // float lerp = baseLerp + (camera.zoom - 1.0f) * 0.5f; // Add offset based on zoom

    // Calculate desired camera position (smooth following)
    float targetX = camera.target.x + (playerPos.x - camera.target.x) * lerp * player.getDeltaTime();
    float targetY = camera.target.y + (playerPos.y - camera.target.y) * lerp * player.getDeltaTime();

    // Define world bounds and screen dimensions
    float worldBounds = 32 * CELL_SIZE;
    float halfScreenWidth = GetScreenWidth() / (2.0f * camera.zoom);
    float halfScreenHeight = GetScreenHeight() / (2.0f * camera.zoom);

    // Calculate camera bounds (world bounds minus half screen size)
    float cameraBoundsX = worldBounds - halfScreenWidth;
    float cameraBoundsY = worldBounds - halfScreenHeight;

    // Clamp camera target so screen edges don't go outside world bounds
    camera.target.x = std::max(-cameraBoundsX, std::min(cameraBoundsX, targetX));
    camera.target.y = std::max(-cameraBoundsY, std::min(cameraBoundsY, targetY));

    // Camera zoom
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        camera.zoom += wheel * 0.1f;
        camera.zoom = Clamp(camera.zoom, 0.8f, 3.0f);
    }

    BeginMode2D(camera);

    // Grid
    for (Cell cell : grid.getCells()) {
        DrawTexturePro(cell.getTexture(), {96, 64 ,CELL_SIZE, CELL_SIZE}, {cell.getPosition().x, cell.getPosition().y ,CELL_SIZE, CELL_SIZE}, { 0, 0 }, 0.0f, WHITE);
    }

    // Player
    DrawCircle(playerPos.x, playerPos.y, PLAYER_RADIUS, RED);

    EndMode2D();

    // UI
    DrawFPS(10, 10);

    std::string initialMessage = "Welcome to the Survivor Game";
    DrawText(initialMessage.c_str(), (this->width/2)-MeasureText(initialMessage.c_str(), 20)/2, 10, UI_FONT_SIZE, LIGHTGRAY);

    // Vector2 sreenPos = GetWorldToScreen2D(player.getPosition(), camera);
    std::string coordinates = std::format("x: {:.1f} y: {:.1f}",
                                 playerPos.x,
                                 playerPos.y);
    DrawText(coordinates.c_str(), 10, 40, 20, BLACK);

    std::string zoomInfo = std::format("Zoom: {:.2f}", camera.zoom);
    DrawText(zoomInfo.c_str(), 10, 65, 16, DARKGRAY);

    EndDrawing();
}

