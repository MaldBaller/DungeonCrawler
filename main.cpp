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
    bool fullScreen = true;


    int gamemode = 0; // 0 = main menu , 1 = dungeon , 2 = shop in beteween 
    std::string buffer;
    
    
    Character player(0, 0, "Hero", {0,0}, {0, 0, 50, 50});
    Texture playerTextures[100];
    for (int i = 0; i < 1; i++){
        buffer = "images/player_" + std::to_string(i) + ".png";
        playerTextures[i] = LoadTexture(buffer.c_str());
    }


    std::vector <Character> enemies;

    enemies.push_back(Character(1,10,"Goblin", {250,0}, {0, 0, 50, 50}));
    

    //character Enemies(3, 3, 3, 3, 1, 1, 5, "Goblin", {screenX / 2.f + 100, screenY / 2.f}, {0, 0, 50, 50}, LoadTexture("resources/enemy.png"), 0.0f, 1.0f);



    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        //Input
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            
        }

        if (IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
        }

        //Game input
        if (gamemode == 1) {
            if (IsKeyDown(KEY_W)){
                player.position.y += player.speed;
                player.rotation = 2;
            }if (IsKeyDown(KEY_S)){
                player.position.y += player.speed;
                player.rotation = 2;
            }if (IsKeyDown(KEY_A)){
                player.position.y += player.speed;
                player.rotation = 2;
            }if (IsKeyDown(KEY_D)){
                player.position.y += player.speed;
                player.rotation = 2;
            }
        }


        // Draw calls
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < 0; i++){
            
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