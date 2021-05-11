#include "raylib.h"

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
            for (int i = 0; i < 8 ; i++) {
                for (int j = 0; j < 6; j++) {
                    bool isEven = (i+j) % 2 == 0;
                    Color color;
                    if (isEven) {
                        color = Fade(GOLD, 0.6f);
                    } else {
                        color = Fade(RED, 0.6f);
                    }
                    DrawRectangle(i*100, j*100, 100, 100, color);
                }
            }
            DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}