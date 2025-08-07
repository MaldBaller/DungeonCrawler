#include "raylib.h"

int main()
{
    // Initialization
    
   

    SetConfigFlags(FLAG_FULLSCREEN_MODE);  // Set fullscreen flag
    InitWindow(0, 0, "DungeonCrawler");


    int screenX = GetScreenWidth();
    int screenY = GetScreenHeight();

    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            
        }


        // Draw calls
        BeginDrawing();
        ClearBackground(BLACK);


        DrawRectangle(screenX / 2.f - 50, screenY / 2.f - 50, 100, 100, RED);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}