#include <algorithm>
#include <cmath>
#include <string>
#include "raylib.h"
#include <iostream>

#include "Enemy.h"
#include "Grid.h"
#include "Player.h"
#include "Screen.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Survivor Game");

    SetTargetFPS(60);

    Player player = Player( 0, 0);

    Screen screen = Screen(screenWidth, screenHeight, player);

    Grid grid = Grid();

    int n = 10;

    std::vector<Enemy> enemies;
    for (int i=0; i<n; i++) {
        Vector2 pos = { (float)GetRandomValue(-31*16, 31*16), (float)GetRandomValue(-31*16, 31*16)};
        enemies.push_back(Enemy(pos));
    }

    while (!WindowShouldClose())
    {
        // Update enemy positions and behavior first
        for (auto& enemy : enemies) {
            enemy.moveToPlayer(player, enemies);
            enemy.update();
        }

        // Remove dead enemies BEFORE processing arrow collisions
        enemies.erase(
            std::remove_if(enemies.begin(), enemies.end(),
                [](Enemy& enemy) {
                    return enemy.getHealth() <= 0;
                }),
            enemies.end()
        );

        // Now update player (including arrow collision detection) with clean enemy list
        player.update(enemies);
        player.handleKeys(enemies);

        // Draw everything
        screen.draw(player, grid, enemies);
    }

    CloseWindow();

    return 0;
}