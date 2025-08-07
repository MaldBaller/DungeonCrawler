#include "character.h"
#include "player.h"
#include <vector>
#include <iostream>

int main()
{
    // Initialization
    
   

    SetConfigFlags(FLAG_FULLSCREEN_MODE);  // Set fullscreen flag
    InitWindow(0, 0, "DungeonCrawler");


    int screenX = GetScreenWidth();
    int screenY = GetScreenHeight();


    std::string buffer;
    Character player(5, 5, 5, 5, 0, 1, 10, "Hero", {screenX / 2.f, screenY / 2.f}, {0, 0, 50, 50}, 0.0f, 1.0f);
    Texture playerTextures[100];
    for (int i = 0; i < 0; i++){
        buffer = "images/player_" + std::to_string(i) + ".png";
        playerTextures[i] = LoadTexture(buffer.c_str());
    }


    std::vector <Character> Enemies;

    //character Enemies(3, 3, 3, 3, 1, 1, 5, "Goblin", {screenX / 2.f + 100, screenY / 2.f}, {0, 0, 50, 50}, LoadTexture("resources/enemy.png"), 0.0f, 1.0f);



    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            
        }


        // Draw calls
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < Enemies.size(); i++){
            
        }


        // Draw player character
        //DrawTexture(Player.texture, screenX / 2.f - 50, screenY / 2.f - 50, WHITE);
        //Player.Draw()
        DrawRectangle(screenX / 2.f - 50, screenY / 2.f - 50, 100, 100, RED);


        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}