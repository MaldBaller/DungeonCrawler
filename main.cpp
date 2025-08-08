#include "character.h"
#include "player.h"
#include "enemy.h"
#include <vector>
#include <iostream>

int main()
{
    InitWindow(1200, 1000, "DungeonCrawler");

    Texture2D playerImage = LoadTexture("resources/player_0.png"); 

    Player player({500, 700}, {0, 0, 50, 50}, playerImage);

    int screenX = GetScreenWidth();
    int screeny = GetScreenHeight();
    
    
    int gamemode = 1;
    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        //std::cout << screenX << "<screen width :)";

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
            screenX = GetScreenWidth();
            screeny = GetScreenHeight();
        }


        // Movement
        if (gamemode == 1) {
            if (IsKeyDown(KEY_W)) player.position.y -= player.speed;
            if (IsKeyDown(KEY_S)) player.position.y += player.speed;
            if (IsKeyDown(KEY_A)) player.position.x -= player.speed;
            if (IsKeyDown(KEY_D)) player.position.x += player.speed;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        if (gamemode == 1){
            player.Draw();
            //DrawRectangle();
        }
        

        EndDrawing();
    }

    UnloadTexture(playerImage);
    CloseWindow();

    return 0;
}
