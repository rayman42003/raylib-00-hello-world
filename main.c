#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

Vector2 safeVector2Normalize(Vector2 v) {
    const float EPSILON = 0.0001;
    if (fabs(v.x) < EPSILON && fabs(v.y) < EPSILON) {
        return Vector2Zero();
    } else {
        return Vector2Normalize(v);
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

    Vector2 leftEye = (Vector2) { .x = 250, .y = 300 };

    Vector2 rightEye = (Vector2) { .x = 550, .y = 300 };

    int eyeSize = 120;
    int pupilSize = 40;
    int borderSize = 30;

    float pupilSpeed = 1000.0f;
    Vector2 prevLeftPupil = leftEye;
    Vector2 prevRightPupil = rightEye;
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

        bool isCloserToLeftEye;
        float distToCloserEye;
        if (distToLeftEye < distToRightEye) {
            isCloserToLeftEye = true;
            distToCloserEye = distToLeftEye;
        } else {
            isCloserToLeftEye = false;
            distToCloserEye = distToRightEye;
        }
        
        Vector2 eyeToMouse = Vector2Subtract(mousePos, isCloserToLeftEye ? leftEye : rightEye);
        eyeToMouse = safeVector2Normalize(eyeToMouse);
        
        float eyeOffset = fmin(distToCloserEye, eyeSize - pupilSize - borderSize);
        Vector2 desiredLeftPupil = Vector2Add(leftEye, Vector2Scale(eyeToMouse, eyeOffset));

        Vector2 pupilMoveDir = safeVector2Normalize(Vector2Subtract(desiredLeftPupil, prevLeftPupil));

        float maxMoveDistance = Vector2Distance(desiredLeftPupil, prevLeftPupil);
        prevLeftPupil = Vector2Add(prevLeftPupil, Vector2Scale(pupilMoveDir, fmin(pupilSpeed * GetFrameTime(), maxMoveDistance)));
        prevRightPupil = Vector2Add(prevRightPupil, Vector2Scale(pupilMoveDir, fmin(pupilSpeed * GetFrameTime(), maxMoveDistance)));

        DrawCircleV(leftEye, eyeSize, LIGHTGRAY);
        DrawCircleV(rightEye, eyeSize, LIGHTGRAY);

        DrawCircleV(prevLeftPupil, pupilSize, BLACK);
        DrawCircleV(prevRightPupil, pupilSize, BLACK);
        
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}