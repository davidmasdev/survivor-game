#include <cmath>
#include <string>
#include "raylib.h"
#include <iostream>

#include "Player.h"
#include "Screen.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Survivor Game");

    SetTargetFPS(60);


    Player player = Player((float)screenWidth/2, (float)screenHeight/2);

    Screen screen = Screen(screenWidth, screenHeight, player);



    while (!WindowShouldClose())
    {
        player.handleKeys();

        screen.draw(player);

    }

    CloseWindow();

    return 0;
}
