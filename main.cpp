#include "character.h"
#include "player.h"
#include <vector>
#include <iostream>
#include "projectile.h"

int main()
{
    InitWindow(1200, 1000, "DungeonCrawler");

    Texture2D playerImage = LoadTexture("resources/knight.png"); 
    Texture2D playerRight = LoadTexture("resources/right_looking_knight.png"); 
    Texture2D playerLeft = LoadTexture("resources/left_looking_knight.png"); 
    Player player({500, 700}, {0, 0, 50, 50}, playerImage);

    int gamemode = 1;

    SetTargetFPS(60);

    typedef enum{
        up,
        down,
        left,
        right
    }Direction;
    Direction playerDir = down;

    while (!WindowShouldClose())
    {
        // Movement
        if (gamemode == 1) {
            if (IsKeyDown(KEY_W)){
                player.position.y -= player.speed;
                playerDir = down;
                player.changeImage(playerImage);

            }
            if (IsKeyDown(KEY_S)){
                player.position.y += player.speed;
                playerDir = up;
                player.changeImage(playerImage);
            }
            if (IsKeyDown(KEY_A)){
                player.position.x -= player.speed;
                playerDir = left;
                player.changeImage(playerLeft);
            }
            if (IsKeyDown(KEY_D)){
                player.position.x += player.speed;
                playerDir = right;
                player.changeImage(playerRight);

            }
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
