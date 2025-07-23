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

    int n = 100;

    std::vector<Enemy> enemies;
    for (int i=0; i<n; i++) {
        Vector2 pos = { (float)GetRandomValue(-31*16, 31*16), (float)GetRandomValue(-31*16, 31*16)};
        enemies.push_back(Enemy(pos));
    }


    while (!WindowShouldClose())
    {
        player.handleKeys();

        screen.draw(player, grid, enemies);

    }

    CloseWindow();

    return 0;
}
