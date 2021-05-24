#include "raylib.h"
#include "stdio.h"

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;


    InitWindow(screenWidth, screenHeight, "raylib");

    SetTargetFPS(60); 

    Vector2 leftEye = (Vector2) { .x = 250, .y = 300 };
    Vector2 leftPupil = leftEye;

    Vector2 rightEye = (Vector2) { .x = 550, .y = 300 };
    Vector2 rightPupil = rightEye;

    int eyeSize = 120;
    int pupilSize = 40;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        Vector2 mousePos =  GetMousePosition();
        char* mousePosText[80];
        sprintf(mousePosText, "Mouse pos: [%.2f, %.2f]", mousePos.x, mousePos.y);
        DrawText(mousePosText, 10, 30, 20, ORANGE);

        DrawCircle(leftEye.x, leftEye.y, eyeSize, LIGHTGRAY);
        DrawCircle(leftPupil.x, leftPupil.y, pupilSize, BLACK);

        DrawCircle(rightEye.x, rightEye.y, eyeSize, LIGHTGRAY);
        DrawCircle(rightPupil.x, rightPupil.y, pupilSize, BLACK);
        
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}