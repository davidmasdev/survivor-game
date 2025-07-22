#include <cmath>
#include <string>
#include "raylib.h"
#include <iostream>

#include "Grid.h"
#include "Player.h"
#include "Screen.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Survivor Game");

    SetTargetFPS(60);

    Player player = Player( 0, 0);

    Screen screen = Screen(screenWidth, screenHeight, player);

    Grid grid = Grid();

    while (!WindowShouldClose())
    {
        player.handleKeys();

        screen.draw(player, grid);

    }

    CloseWindow();

    return 0;
}
