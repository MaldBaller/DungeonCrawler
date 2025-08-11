#include "character.h"
#include "player.h"
#include "enemy.h"
#include <vector>
#include <iostream>
#include <random>
#include "sword.h"

int randint(int min, int max) {
	return (rand() + rand()) % (max + 1 - min) + min;
}

int main()
{
    srand(time(NULL));
    InitWindow(1200, 1000, "DungeonCrawler");

    Texture2D playerImage = LoadTexture("resources/player_0.png"); 

    Player player({0, 0}, {0,0,32*4,32*4}, playerImage);
    Sword sword(LoadTexture("resources/sword_0.png"),10);
    int weapon = 0; //0 is sword 1 is mage
    std::vector <Enemy> enemy;

    for(int i = 0; i < 2; i++){
        enemy.push_back(Enemy( {float(randint(-400,400)),float(randint(-400,400))}, {0,0,32*4,32*4}, LoadTexture("resources/enemy_0_0.png"), 50.0));
    }

    int screenX = GetScreenWidth();
    int screeny = GetScreenHeight();
    
    
    int gamemode = 1;
    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        //std::cout << screenX << "<screen width";

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
            screenX = GetScreenWidth();
            screeny = GetScreenHeight();
        }


        // Movement
        if (gamemode == 1) {
            if (IsKeyDown(KEY_W)) {player.position.y -= player.speed; player.rotation = 0.f;}
            if (IsKeyDown(KEY_S)) {player.position.y += player.speed; player.rotation = 180.f;}
            if (IsKeyDown(KEY_A)) {player.position.x -= player.speed; player.rotation = 270.f;}
            if (IsKeyDown(KEY_D)) {player.position.x += player.speed; player.rotation = 90.f;}
            player.hitbox.x = player.position.x;
            player.hitbox.y = player.position.y;
        
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                if (weapon == 0){
                    if (sword.cooldownFrame == 0) { sword.cooldownFrame = -1;}
                }else{

                }
            }
            
            if (weapon == 0) {
                sword.Slash(enemy,player.rotation);
                
            }
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
            sword.Draw(player.rotation);
            
        }
        

        EndDrawing();
    }
    
    UnloadTexture(playerImage);
    CloseWindow();

    return 0;
}
