#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

typedef struct Grid {
    int row;
    int col;
    Vector2 startingPos;
    Vector2 cellDimensions;
} Grid;

void drawGrid(Grid grid) {
    int row = grid.row;
    int col = grid.col;
    Vector2 startingPos = grid.startingPos;
    Vector2 cellDimensions = grid.cellDimensions;

    float endX = startingPos.x + cellDimensions.x * col;
    for (int i = 0; i <= row; i++) {
        float currY = startingPos.y + cellDimensions.y * i; 
        DrawLineV((Vector2){ .x = startingPos.x, .y = currY }, 
            (Vector2){ .x = endX, .y = currY }, LIGHTGRAY);
    }

    float endY = startingPos.y + cellDimensions.y * row;
    for (int i = 0; i <= col; i++) {
        float currX = startingPos.x + cellDimensions.x * i;
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
    Grid grid = (Grid) {
        .row = 16,
        .col = 24,
        .startingPos = (Vector2)  { .x = 100, .y = 100 },
        .cellDimensions = (Vector2) { .x = 25, .y = 25 }
    };
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        drawGrid(grid);
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}