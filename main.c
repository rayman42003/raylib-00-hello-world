#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

void drawGrid(int row, int col, Vector2 startingPos, Vector2 squareDimensions) {
    float endX = startingPos.x + squareDimensions.x * col;
    for (int i = 0; i <= row; i++) {
        float currY = startingPos.y + squareDimensions.y * i; 
        DrawLineV((Vector2){ .x = startingPos.x, .y = currY }, 
            (Vector2){ .x = endX, .y = currY }, LIGHTGRAY);
    }

    float endY = startingPos.y + squareDimensions.y * row;
    for (int i = 0; i <= col; i++) {
        float currX = startingPos.x + squareDimensions.x * i;
        DrawLineV((Vector2){ .x = currX, .y = startingPos.y },
            (Vector2){ .x = currX, .y = endY }, LIGHTGRAY);
    }
}

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
        drawGrid(16, 24, (Vector2) { .x = 100, .y = 100 }, (Vector2) { .x = 25, .y = 25 });
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}