cmake_minimum_required(VERSION 3.31)
project(survivor_game)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
)

# ImGui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
        GIT_TAG "docking"
        GIT_PROGRESS TRUE
)

# rlImGui
FetchContent_Declare(
        rlimgui
        GIT_REPOSITORY "https://github.com/raylib-extras/rlImGui.git"
        GIT_TAG "main"
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib imgui rlimgui)

# Create ImGui library
add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

# Create rlImGui library
add_library(rlimgui STATIC
        ${rlimgui_SOURCE_DIR}/rlImGui.cpp
)

target_include_directories(rlimgui PUBLIC
        ${rlimgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}
)

target_link_libraries(rlimgui PUBLIC imgui raylib)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

# Declaring our executable
add_executable(${PROJECT_NAME}
        src/Player.h
        src/Player.cpp
        src/Screen.cpp
        src/Screen.h
        src/Grid.cpp
        src/Grid.h
        src/Cell.cpp
        src/Cell.h
        src/Enemy.cpp
        src/Enemy.h
        src/Arrow.cpp
        src/Arrow.h)
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib rlimgui)

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
