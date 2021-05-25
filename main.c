#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    const float EPSILON = 0.0001;


    InitWindow(screenWidth, screenHeight, "raylib");

    SetTargetFPS(60); 

    Vector2 leftEye = (Vector2) { .x = 250, .y = 300 };
    Vector2 leftPupil = leftEye;

    Vector2 rightEye = (Vector2) { .x = 550, .y = 300 };
    Vector2 rightPupil = rightEye;

    int eyeSize = 120;
    int pupilSize = 40;
    int borderSize = 30;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        Vector2 mousePos =  GetMousePosition();
        char* mousePosText[80];
        sprintf(mousePosText, "Mouse pos: [%.2f, %.2f]", mousePos.x, mousePos.y);
        DrawText(mousePosText, 10, 30, 20, ORANGE);

        float distToLeftEye = fabs(Vector2Distance(mousePos, leftEye));
        float distToRightEye = fabs(Vector2Distance(mousePos, rightEye));

        Vector2 closerEye;
        Vector2 furtherEye;
        float distToCloserEye;
        if (distToLeftEye < distToRightEye) {
            closerEye = leftEye;
            furtherEye = rightEye;
            distToCloserEye = distToLeftEye;
        } else {
            closerEye = rightEye;
            furtherEye = leftEye;
            distToCloserEye = distToRightEye;
        }
        
        Vector2 eyeToMouse = Vector2Subtract(mousePos, closerEye);
        if (fabs(eyeToMouse.x) < EPSILON && fabs(eyeToMouse.y) < EPSILON) {
            eyeToMouse = Vector2Zero();
        } else {
            eyeToMouse = Vector2Normalize(eyeToMouse);
        }
        
        float eyeOffset = fmin(distToCloserEye, eyeSize - pupilSize - borderSize);
        closerEye = Vector2Add(closerEye, Vector2Scale(eyeToMouse, eyeOffset));
        furtherEye = Vector2Add(furtherEye, Vector2Scale(eyeToMouse, eyeOffset));

        DrawCircle(leftEye.x, leftEye.y, eyeSize, LIGHTGRAY);
        DrawCircle(rightEye.x, rightEye.y, eyeSize, LIGHTGRAY);

        DrawCircle(closerEye.x, closerEye.y, pupilSize, BLACK);
        DrawCircle(furtherEye.x, furtherEye.y, pupilSize, BLACK);
        
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}