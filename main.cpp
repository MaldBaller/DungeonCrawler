#include "character.h"
#include "player.h"
#include "enemy.h"
#include <vector>
#include <iostream>
#include "projectile.h"
#include <random>
#include "sword.h"

int randint(int min, int max) {
	return (rand() + rand()) % (max + 1 - min) + min;
}


int main()
{
    srand(time(NULL));
    InitWindow(1200, 1000, "DungeonCrawler");

    Texture2D playerImage = LoadTexture("resources/knight.png"); 
    Texture2D playerRight = LoadTexture("resources/right_looking_knight.png"); 
    Texture2D playerLeft = LoadTexture("resources/left_looking_knight.png"); 

    Player player({0, 0}, {0,0,32*4,32*4}, playerImage);
    Sword sword(LoadTexture("resources/sword_0.png"),1);
    int weapon = 0; //0 is sword 1 is mage
    std::vector <Enemy> enemy;

    for(int i = 0; i < 2; i++){
        enemy.push_back(Enemy( {float(randint(-400,400)),float(randint(-400,400))}, {0,0,32*4,32*4}, LoadTexture("resources/enemy_0_0.png"), 50.0));
    }

    int screenX = GetScreenWidth();
    int screeny = GetScreenHeight();
    
    
    int gamemode = 1;
    SetTargetFPS(120);

    typedef enum{
        up,
        down,
        left,
        right
    }Direction;
    Direction playerDir = down;

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
<<<<<<< HEAD
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
=======
            if (IsKeyDown(KEY_W)) {player.position.y -= player.speed; player.rotation = 0.f;}
            if (IsKeyDown(KEY_S)) {player.position.y += player.speed; player.rotation = 180.f;}
            if (IsKeyDown(KEY_A)) {player.position.x -= player.speed; player.rotation = 270.f;}
            if (IsKeyDown(KEY_D)) {player.position.x += player.speed; player.rotation = 90.f;}
>>>>>>> Chris-features
            player.hitbox.x = player.position.x;
            player.hitbox.y = player.position.y;
        
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                if (weapon == 0){
                    if (sword.cooldownFrame == 0) { sword.cooldownFrame = -1;}
                }else{

                }
            }
            
<<<<<<< HEAD


                

            
=======
           
>>>>>>> Chris-features
        }

        BeginDrawing();
        ClearBackground(BLACK);
        if (gamemode == 1){

            //Enemy draw
            for (int i = 0; i < enemy.size(); i++){
                
                enemy.at(i).FollowPlayer(player.position);
                enemy.at(i).Draw(player.position);

                if (FindDistance(enemy.at(i).position, player.position) < 50){
                    enemy.at(i).Move(enemy.at(i).speed * 1.1 * cos(GetAngleBetweenPoints(player.position,enemy.at(i).position)) , enemy.at(i).speed * 1.1 * sin(GetAngleBetweenPoints(player.position,enemy.at(i).position)) );
                }
                    
                for (int j = 0; j < enemy.size(); j++){
                    if (j != i) {
                        if (FindDistance(enemy.at(i).position, enemy.at(j).position) < 50){
                            enemy.at(i).Move(enemy.at(i).speed * 1.1 * cos(GetAngleBetweenPoints(enemy.at(j).position,enemy.at(i).position)) , enemy.at(i).speed * 1.1 * sin(GetAngleBetweenPoints(enemy.at(j).position,enemy.at(i).position)) );
                        }
                    }
                }
                if (sword.cooldownFrame == -1){
                    if(FindDistance(enemy[i].position,player.position) < 185) {
                        
                        if ((player.rotation == 0.f && player.position.y > enemy[i].position.y) || (player.rotation == 180 && player.position.y < enemy[i].position.y) || (player.rotation == 90 && player.position.x < enemy[i].position.x) || (player.rotation == 270 && player.position.x > enemy[i].position.x)){
                            enemy[i].health -= sword.damage;
                            enemy[i].Move(30 * cos(GetAngleBetweenPoints(player.position,enemy[i].position)),30 * sin(GetAngleBetweenPoints(player.position,enemy[i].position)));
                        }
                    }
                }
                if (enemy[i].health < 0){

                }

            }

            if (weapon == 0) {
                if (sword.cooldownFrame != 0){ sword.Slash();}
                /*
                if (sword.cooldownFrame == -1){
                    for(int i; i < enemy.size(); i++) {
                        if(FindDistance(enemy[i].position,player.position) < 60) {
                            if ((player.rotation == 0 && player.position.y > enemy[i].position.y) || (player.rotation == 180 && player.position.y < enemy[i].position.y) || (player.rotation == 90 && player.position.x > enemy[i].position.x) || (player.rotation == 270 && player.position.x < enemy[i].position.x)){
                                enemy[i].health -= sword.damage;
                                enemy[i].Move(3 * cos(GetAngleBetweenPoints(player.position,enemy[i].position)),3 * sin(GetAngleBetweenPoints(player.position,enemy[i].position)));
                            } 

                        }
                    }

                }
                */
            }

       
        
            player.Draw();
            DrawRectangleLines(float(GetScreenWidth() / 2.f - 16 * 4), float(GetScreenHeight() / 2.f - 16 * 4),player.hitbox.width,player.hitbox.height,RED);
            sword.Draw(player.rotation);
            DrawCircleLines(float(GetScreenWidth() / 2.f), float(GetScreenHeight() / 2.f),185,WHITE);
            
        }
        

        EndDrawing();
    }
    
    UnloadTexture(playerImage);
    CloseWindow();

    return 0;
}
