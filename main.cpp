#include "raylib.h"

int main()
{
    // Initialization
    
   

    SetConfigFlags(FLAG_FULLSCREEN_MODE);  // Set fullscreen flag
    InitWindow(0, 0, "DungeonCrawler");

    //int screenWidth = getWindowWidth().x;
   // int screenHeight = getWindowWidth().y;

    SetTargetFPS(120);
    while (!WindowShouldClose())
    {



        // Draw calls
        BeginDrawing();

        ClearBackground(DARKGREEN);

        
        EndDrawing();
    }
    CloseWindow();
}