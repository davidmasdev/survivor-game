#include <algorithm>
#include <iostream>
#include <string>
#include "raylib.h"
#include "rlImGui.h"

#include "Enemy.h"
#include "Grid.h"
#include "imgui.h"
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

    int n = 2;

    std::vector<Enemy> enemies;
    for (int i=0; i<n; i++) {
        // TODO: Dont allow enemy to appear next to a player
        Vector2 pos = { (float)GetRandomValue(-31*16, 31*16), (float)GetRandomValue(-31*16, 31*16)};
        enemies.push_back(Enemy(pos));
    }

    rlImGuiSetup(true);
    bool waveCleared = false;
    bool nextWave = false;
    bool gameOver = false;


    while (!WindowShouldClose())
    {

        if (enemies.empty()) waveCleared = true;
        if (player.getHealth()<=0) gameOver = true;

        if (!waveCleared && !gameOver) {
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

        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw everything
        screen.draw(player, grid, enemies);

        // Always call rlImGuiBegin() and rlImGuiEnd() together
        rlImGuiBegin();

        if (gameOver) {

            ImGui::Begin("GAME OVER");

            ImGui::Text("You Lost!");
            if (ImGui::Button("Replay")) {
                gameOver = false;
                player = Player({0,0});

                n = 2;
                enemies.clear();

                for (int i=0; i<n; i++) {
                    // TODO: Dont allow enemy to appear next to a player
                    Vector2 pos = { (float)GetRandomValue(-31*16, 31*16), (float)GetRandomValue(-31*16, 31*16)};
                    enemies.push_back(Enemy(pos));
                }
            }
            if (ImGui::Button("Quit")) {
                ImGui::End();
                rlImGuiEnd();
                EndDrawing();
                rlImGuiShutdown();
                CloseWindow();
                return 0;
            }

            ImGui::End();
        }

        if (waveCleared) {
            ImGui::Begin("Wave Cleared");

            ImGui::Text("You cleared the wave!");
            ImGui::Text("Choose an upgrade");
            if (ImGui::Button("Speed")) {
                player.upgradeSpeed(20.0f);
                nextWave = true;
            }
            if (ImGui::Button("Health")) {
                player.upgradeHealth(1.0f);
                nextWave = true;
            }
            if (ImGui::Button("Arrow Cooldown")) {
                player.upgradeCooldown(0.2f);
                nextWave = true;
            }

            ImGui::End();
        }

        rlImGuiEnd();  // Always call this every frame

        if (nextWave) {
            // Start next wave
            n += (n/2) + 1; // spawn new wave of enemies
            for (int i = 0; i < n; i++) {
                Vector2 pos = { (float)GetRandomValue(-31*16, 31*16), (float)GetRandomValue(-31*16, 31*16)};
                enemies.push_back(Enemy(pos));
            }

            waveCleared = false;
            nextWave = false;
        }

        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}