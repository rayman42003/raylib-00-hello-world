#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include "math.h"

typedef struct IntVector2 {
    int x;
    int y;
} IntVector2;

typedef struct Grid {
    int row;
    int col;
    Vector2 startingPos;
    Vector2 cellDimensions;
    char** values;
} Grid;

Vector2 getGridCellCenter(Grid grid, IntVector2 cell) {
    if (cell.x < 0 || cell.x >= grid.col || cell.y < 0 || cell.y >= grid.row) {
        return (Vector2) { .x = -1, .y = -1 };
    }
    return (Vector2) { .x = (cell.x + 0.5f) * grid.cellDimensions.x + grid.startingPos.x, 
        .y = (cell.y + 0.5f) * grid.cellDimensions.y + grid.startingPos.y };
}

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

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            char cellValue = grid.values[i][j];
            if (cellValue != ' ') {
                Vector2 cellCenter = getGridCellCenter(grid, (IntVector2) { .x = i, .y = j });
                Vector2 textStart = Vector2Subtract(cellCenter, Vector2Scale(grid.cellDimensions, 0.25f));
                int fontSize = (int) (fmax(grid.cellDimensions.x, grid.cellDimensions.y) / 1.75);
                DrawText(&cellValue, textStart.x, textStart.y, fontSize, BLACK);
            }
        }
    }
}

IntVector2 getGridCell(Grid grid, Vector2 pos) {
    Vector2 originPos = Vector2Subtract(pos, grid.startingPos);
    float originPosX = originPos.x;
    float originPosY = originPos.y;
    float maxX = grid.cellDimensions.x * grid.col;
    float maxY = grid.cellDimensions.y * grid.row;
    if (originPosX < 0 || originPosX > maxX || originPosY < 0 || originPosY > maxY) {
        return (IntVector2) { .x = -1, .y = -1 };
    }
    int cellX = (int) (originPosX / grid.cellDimensions.x);
    int cellY = (int) (originPosY / grid.cellDimensions.y);
    return (IntVector2) { .x = cellX, .y = cellY };
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
    char** gridValues = malloc(grid.col * sizeof(char*));
    for (int i = 0; i < grid.col; i++) {
        gridValues[i] = malloc(grid.row * sizeof(char));
        for (int j = 0; j < grid.row; j ++) {
            gridValues[i][j] = ' ';
        }
    }
    grid.values = gridValues;

    IntVector2 clickedCell = (IntVector2) { .x = -1, .y = -1};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            clickedCell = getGridCell(grid, GetMousePosition());
            grid.values[clickedCell.x][clickedCell.y] = 'x';
        }
        char* clickedCellMsg[80];
        sprintf(clickedCellMsg, "Cell clicked: [%d, %d]", clickedCell.x, clickedCell.y);
        DrawText(clickedCellMsg, 10, 30, 20, ORANGE);

        Vector2 boxCenter = getGridCellCenter(grid, clickedCell);
        char* boxCenterMsg[80];
        sprintf(boxCenterMsg, "Box center pos: [%0.2f, %0.2f]", boxCenter.x, boxCenter.y);
        DrawText(boxCenterMsg, 10, 50, 20, ORANGE);

        drawGrid(grid);

        DrawFPS(10, 10);
        EndDrawing();
    }

    for (int i = 0; i < grid.col; i++) {
        free(grid.values[i]);
    }
    free(grid.values);

    CloseWindow();
    return 0;
}