#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

Vector2 getMoveVector() {
    float EPSILON = 0.0001f;
    Vector2 moveDirection = Vector2Zero();
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        moveDirection.y -= 1.0f;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        moveDirection.y += 1.0f;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        moveDirection.x -= 1.0f;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        moveDirection.x += 1.0f;
    }
    if (fabs(moveDirection.x) < EPSILON && fabs(moveDirection.y) < EPSILON)  {
        return Vector2Zero();
    } else {
        return Vector2Normalize(moveDirection);
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
    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;
    float moveSpeed = 200.0f;
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        Vector2 moveVector = getMoveVector();
        centerX += (moveVector.x * moveSpeed * deltaTime);
        centerY += (moveVector.y * moveSpeed * deltaTime);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTriangle((Vector2){ .x = centerX, .y = centerY},
                         (Vector2){ .x = centerX + 80.0f, .y = centerY},
                         (Vector2){ .x = centerX, .y = centerY - 90.0f}, RED);
        DrawText("This is a triangle", 10, 40, 20, DARKGRAY);
        char posStr[36];
        sprintf(posStr, "Center: [%.3f, %.3f]", centerX, centerY);
        DrawText(posStr, 10, 70, 20, DARKGRAY);
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}