#include "character.h"
#include "player.h"
#include <vector>
#include <iostream>

int main()
{
    InitWindow(1200, 1000, "DungeonCrawler");

    Texture2D playerImage = LoadTexture("resources/player_0.png"); 

    Player player({500, 700}, {0, 0, 50, 50}, playerImage);

    int gamemode = 1;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Movement
        if (gamemode == 1) {
            if (IsKeyDown(KEY_W)) player.position.y -= player.speed;
            if (IsKeyDown(KEY_S)) player.position.y += player.speed;
            if (IsKeyDown(KEY_A)) player.position.x -= player.speed;
            if (IsKeyDown(KEY_D)) player.position.x += player.speed;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        player.Draw();

        EndDrawing();
    }

    UnloadTexture(playerImage);
    CloseWindow();

    return 0;
}
