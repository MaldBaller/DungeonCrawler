#include "character.h"
#include "player.h"
#include "enemy.h"
#include <vector>
#include <iostream>
#include <random>

int randint(int min, int max) {
	return (rand() + rand()) % (max + 1 - min) + min;
}

int main()
{
    srand(time(NULL));
    InitWindow(1200, 1000, "DungeonCrawler");

    Texture2D playerImage = LoadTexture("resources/player_0.png"); 

    Player player({0, 0}, {0,0,32*4,32*4}, playerImage);
    std::vector <Enemy> enemy;

    for(int i = 0; i < 2; i++){
        enemy.push_back(Enemy( {float(randint(-400,400)),float(randint(-400,400))}, {0,0,32*4,32*4}, LoadTexture("resources/enemy_0_0.png")));
    }

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
            player.hitbox.x = player.position.x;
            player.hitbox.y = player.position.y;
            


        }

        BeginDrawing();
        ClearBackground(BLACK);
        if (gamemode == 1){

            //Enemy draw
            for (int i = 0; i < enemy.size(); i++){
                enemy.at(i).Draw(player.position);
                enemy.at(i).FollowPlayer(player.position);
                for (int j = 0; j < enemy.size(); j++){
                    if (j != i) {
                        if (FindDistance(enemy.at(i).position, enemy.at(j).position) < 50){
                            enemy.at(i).Move(enemy.at(i).speed * 1.1 * cos(GetAngleBetweenPoints(enemy.at(j).position,enemy.at(i).position)) , enemy.at(i).speed * 1.1 * sin(GetAngleBetweenPoints(enemy.at(j).position,enemy.at(i).position)) );
                        }
                    }
                }
            }

            player.Draw();
             DrawRectangleLines(float(GetScreenWidth() / 2.f - 16 * 4), float(GetScreenHeight() / 2.f - 16 * 4),player.hitbox.width,player.hitbox.height,RED);

            
        }
        

        EndDrawing();
    }

    UnloadTexture(playerImage);
    CloseWindow();

    return 0;
}
