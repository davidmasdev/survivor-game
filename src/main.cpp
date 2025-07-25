#include <algorithm>
#include <cmath>
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

        // Enhanced UI with improved styling and effects
        rlImGuiBegin();

        // Set up custom colors and styles
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        // Store original colors to restore later
        static bool colorsInitialized = false;
        static ImVec4 originalColors[ImGuiCol_COUNT];
        if (!colorsInitialized) {
            memcpy(originalColors, colors, sizeof(ImVec4) * ImGuiCol_COUNT);
            colorsInitialized = true;
        }

        if (gameOver) {
            // Dark red theme for game over
            colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.0f, 0.0f, 0.95f);
            colors[ImGuiCol_TitleBg] = ImVec4(0.6f, 0.0f, 0.0f, 0.8f);
            colors[ImGuiCol_TitleBgActive] = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);
            colors[ImGuiCol_Button] = ImVec4(0.5f, 0.1f, 0.1f, 0.8f);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.7f, 0.2f, 0.2f, 1.0f);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.9f, 0.3f, 0.3f, 1.0f);

            // Center the window
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(400, 250), ImGuiCond_Always);

            ImGui::Begin("GAME OVER", nullptr,
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

            // Add some spacing and centering
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("You have been defeated!").x) * 0.5f);

            // Animated text color
            float time = (float)GetTime();
            float pulse = (sin(time * 3.0f) + 1.0f) * 0.5f;
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.3f + pulse * 0.4f, 0.3f + pulse * 0.4f, 1.0f));
            ImGui::Text("You have been defeated!");
            ImGui::PopStyleColor();

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            // Stylized buttons with icons
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 280) * 0.5f);

            // Replay button with green accent
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 0.2f, 0.8f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));

            if (ImGui::Button("Play Again", ImVec2(120, 40))) {
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
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 20);

            // Quit button with red accent
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.2f, 0.2f, 0.8f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.3f, 0.3f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));

            if (ImGui::Button("Quit Game", ImVec2(120, 40))) {
                ImGui::PopStyleColor(3); // Pop the quit button colors first
                ImGui::End();
                // Restore original colors before cleanup
                memcpy(colors, originalColors, sizeof(ImVec4) * ImGuiCol_COUNT);
                rlImGuiEnd();
                EndDrawing();
                rlImGuiShutdown();
                CloseWindow();
                return 0;
            }
            ImGui::PopStyleColor(3);

            ImGui::End();
        }

        if (waveCleared) {
            // Golden theme for wave cleared
            colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.0f, 0.95f);
            colors[ImGuiCol_TitleBg] = ImVec4(0.6f, 0.5f, 0.0f, 0.8f);
            colors[ImGuiCol_TitleBgActive] = ImVec4(0.8f, 0.7f, 0.0f, 1.0f);
            colors[ImGuiCol_Button] = ImVec4(0.4f, 0.3f, 0.1f, 0.8f);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.6f, 0.5f, 0.2f, 1.0f);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.8f, 0.7f, 0.3f, 1.0f);
            colors[ImGuiCol_Header] = ImVec4(0.5f, 0.4f, 0.1f, 0.8f);

            // Center the window
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(450, 350), ImGuiCond_Always);

            ImGui::Begin("WAVE CLEARED!", nullptr,
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse);

            // Celebration text with animation
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Congratulations, warrior!").x) * 0.5f);
            float time = (float)GetTime();
            float glow = (sin(time * 2.0f) + 1.0f) * 0.5f;
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f + glow * 0.2f, 0.2f, 1.0f));
            ImGui::Text("Congratulations, warrior!");
            ImGui::PopStyleColor();

            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("You have conquered this wave!").x) * 0.5f);
            ImGui::Text("You have conquered this wave!");

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Choose your reward:").x) * 0.5f);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.9f, 0.7f, 1.0f));
            ImGui::Text("Choose your reward:");
            ImGui::PopStyleColor();

            ImGui::Spacing();
            ImGui::Spacing();

            // Upgrade buttons with descriptions and icons
            float buttonWidth = 380.0f;
            float buttonHeight = 50.0f;
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - buttonWidth) * 0.5f);

            // Speed upgrade
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.4f, 0.8f, 0.8f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.5f, 0.9f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.6f, 1.0f, 1.0f));

            if (ImGui::Button("Swift Movement (+20 Speed)", ImVec2(buttonWidth, buttonHeight))) {
                player.upgradeSpeed(20.0f);
                nextWave = true;
            }
            ImGui::PopStyleColor(3);

            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Move faster to dodge enemy attacks!");
            }

            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - buttonWidth) * 0.5f);

            // Health upgrade
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.4f, 0.8f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.5f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.3f, 0.6f, 1.0f));

            if (ImGui::Button("Vitality Boost (+1 Health)", ImVec2(buttonWidth, buttonHeight))) {
                player.upgradeHealth(1.0f);
                nextWave = true;
            }
            ImGui::PopStyleColor(3);

            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Increase your survivability!");
            }

            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - buttonWidth) * 0.5f);

            // Cooldown upgrade
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.2f, 0.8f, 0.8f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.3f, 0.9f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.4f, 1.0f, 1.0f));

            if (ImGui::Button("Rapid Fire (-0.2s Cooldown)", ImVec2(buttonWidth, buttonHeight))) {
                player.upgradeCooldown(0.2f);
                nextWave = true;
            }
            ImGui::PopStyleColor(3);

            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Shoot arrows more frequently!");
            }

            ImGui::End();
        }

        // Restore original colors when no special UI is showing
        if (!gameOver && !waveCleared) {
            memcpy(colors, originalColors, sizeof(ImVec4) * ImGuiCol_COUNT);
        }

        rlImGuiEnd();

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