#include <stdio.h>

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib");

    SetTargetFPS(60); 
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        float centerX = screenWidth / 2.0f;
        float centerY = screenHeight / 2.0f;
        DrawTriangle((Vector2){ .x = centerX, .y = centerY},
                         (Vector2){ .x = centerX + 80.0f, .y = centerY},
                         (Vector2){ .x = centerX, .y = centerY - 90.0f}, RED);
        DrawText("This is a triangle", 10, 40, 20, DARKGRAY);
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}