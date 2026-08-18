# Survivor Game

Survivor Game is a small top-down action game written in C++. The goal is to survive increasingly difficult waves of enemies using your bow and movement skills.

The game uses [raylib](https://www.raylib.com/) for graphics and [Dear ImGui](https://github.com/ocornut/imgui) for its menus.

## Gameplay

Enemies move toward the player and cause damage when they get close. Shoot them with arrows and clear the whole wave to continue.

After finishing a wave, you can choose one upgrade:

- Increase movement speed
- Gain one health point
- Reduce the delay between shots

Each new wave contains more enemies. The game ends when the player's health reaches zero. From the game-over screen, you can start again or quit.

The screen displays your health, current wave, number of remaining enemies, position, frame rate, and camera zoom.

## Controls

| Action | Control |
| --- | --- |
| Move | `WASD` or arrow keys |
| Shoot | `Space` |
| Zoom camera | Mouse wheel |
| Choose an upgrade | Left mouse button |
| Close the game | `Escape` or the window close button |

Arrows are fired in the last direction the player moved.

## Requirements

You need:

- A C++23-compatible compiler
- CMake 3.31 or newer
- Git
- OpenGL and X11 development libraries
- An internet connection during the first configuration, because CMake downloads raylib, Dear ImGui, and rlImGui

On Ubuntu or Debian, install the required tools and libraries with:

```bash
sudo apt update
sudo apt install build-essential cmake git \
  libx11-dev libxrandr-dev libxinerama-dev \
  libxcursor-dev libxi-dev libgl1-mesa-dev
```

## Building

From the project directory, configure and compile the game:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

The first configuration can take a while because the dependencies are downloaded and built from source.

For a development build with debug information, use:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```

## Running

After building, run:

```bash
./build/survivor_game
```

The texture paths are included when the game is compiled, so the executable can be launched from a different working directory as long as the original `resources` directory still exists.

## Project layout

```text
survivor-game/
├── CMakeLists.txt       Build configuration
├── resources/textures  Game sprites and tiles
└── src                  Game source code
```

The main classes are `Player`, `Enemy`, `Arrow`, `Grid`, `Cell`, and `Screen`. The main game loop and wave handling are in `src/main.cpp`.
