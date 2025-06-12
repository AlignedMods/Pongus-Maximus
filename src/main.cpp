#include "test.hpp"
#include "raylib.h"

int main() {
    InitWindow(800, 400, "Gonner game!");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawRectangle(100, 200, 300, 100, RED);

        DrawText("good boy :3", 200, 50, 30, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}