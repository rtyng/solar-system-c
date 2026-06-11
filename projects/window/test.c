#include <raylib.h>

int main(void)
{
    InitWindow(800, 450, "Hello Raylib");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello Graphics!", 250, 200, 30, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}