#include "character.h"
#include "player.h"
#include "enemy.h"
#include <vector>
#include <iostream>
#include "projectile.h"
#include <random>
#include "sword.h"
#include "health.h"

int randint(int min, int max) {
	return (rand() + rand()) % (max + 1 - min) + min;
}


int main()
{
    srand(time(NULL));
    InitWindow(1200, 1000, "DungeonCrawler");

    std::string buffer;

    Texture2D playerUp = LoadTexture("resources/knight_back.png"); 
    Texture2D playerDown = LoadTexture("resources/knight.png"); 
    Texture2D playerRight = LoadTexture("resources/right_looking_knight.png"); 
    Texture2D playerLeft = LoadTexture("resources/left_looking_knight.png"); 
    Texture2D playerWalk[8];
    for (int i = 0; i < 8; i++){
        buffer = "resources/walk_" + std::to_string(i) + ".png";
        playerWalk[i] = LoadTexture(buffer.c_str());
    }

    Player player({0, 0}, {0,0,32*4,32*4}, playerUp,100);
    Sword sword(LoadTexture("resources/sword_0.png"),4);
    std::vector <Projectile> projectile;
    int weapon = 0; //0 is sword 1 is mage
    Bar bar(10);
    std::vector <Enemy> enemy;

    for(int i = 0; i < 4; i++){
        enemy.push_back(Enemy( {float(randint(-900,900)),float(randint(-900,900))}, {0,0,32*4,32*4}, LoadTexture("resources/slime.png"), 50.0, randint(0,1),30));
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
            //player.changeImage(playerDown);
            player.isWalking = false;
            if (player.frame > player.maxFrame) { player.frame = 0;}
            if (IsKeyDown(KEY_W)){
                player.position.y -= player.speed;
                playerDir = down;
                player.rotation = 0.f;
                if (player.frame < 15 ){
                    player.changeImage(playerWalk[6]);
                }else if (player.frame < 30 ){
                    player.changeImage(playerUp);
                }else if (player.frame < 45 ){
                    player.changeImage(playerWalk[7]);
                }else if (player.frame < 60 ){
                    player.changeImage(playerUp);
                }
                
                player.isWalking = true;
            }
            if (IsKeyDown(KEY_S)){
                player.position.y += player.speed;
                playerDir = up;
                player.rotation = 180.f;
                if (player.frame < 15 ){
                    player.changeImage(playerWalk[4]);
                }else if (player.frame < 30 ){
                    player.changeImage(playerDown);
                }else if (player.frame < 45 ){
                    player.changeImage(playerWalk[5]);
                }else if (player.frame < 60 ){
                    player.changeImage(playerDown);
                }

                player.isWalking = true;
            }
            if (IsKeyDown(KEY_A)){
                player.position.x -= player.speed;
                playerDir = left;
                player.rotation = 270.f;
                if (player.frame < 15 ){
                    player.changeImage(playerWalk[0]);
                }else if (player.frame < 30 ){
                    player.changeImage(playerLeft);
                }else if (player.frame < 45 ){
                    player.changeImage(playerWalk[1]);
                }else if (player.frame < 60 ){
                    player.changeImage(playerLeft);
                }

                player.isWalking = true;
            }
            if (IsKeyDown(KEY_D)){
                player.position.x += player.speed;
                playerDir = right;
                player.rotation = 90.f;
                if (player.frame < 15 ){
                    player.changeImage(playerWalk[2]);
                }else if (player.frame < 30 ){
                    player.changeImage(playerRight);
                }else if (player.frame < 45 ){
                    player.changeImage(playerWalk[3]);
                }else if (player.frame < 60 ){
                    player.changeImage(playerRight);
                }

                player.isWalking = true;
            }
            if (!player.isWalking) { player.frame = 0; player.changeImage(playerDown);} else { player.frame++; }

            player.hitbox.x = player.position.x;
            player.hitbox.y = player.position.y;
        
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                if (weapon == 0){
                    if (sword.cooldownFrame == 0) { sword.cooldownFrame = -1;}
                }else{

                }
            }
            
            
        }

        BeginDrawing();
        ClearBackground(BLACK);
        if (gamemode == 1){

            //Enemy draw
            for (int i = 0; i < enemy.size(); i++){

                enemy.at(i).FollowPlayer(player.position);
                

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
                            enemy[i].Move(10 * cos(GetAngleBetweenPoints(player.position,enemy[i].position)),10 * sin(GetAngleBetweenPoints(player.position,enemy[i].position)));
                        }
                    }
                }

                if (enemy[i].cooldown > 0){enemy[i].cooldown--;}
                if (enemy[i].cooldown == -1 && enemy[i].type == 1){
                    projectile.push_back(Projectile(LoadTexture("resources/mid_flame.png"),enemy[i].damage/5.f,enemy[i].position,GetAngleBetweenPoints(enemy[i].position,player.position),10,60,1));
                    enemy[i].cooldown = 600;
                }if (enemy[i].cooldown == -1 && enemy[i].type == 0){
                    player.health -= enemy[i].damage;
                    player.position += {20 * cos(GetAngleBetweenPoints(enemy[i].position,player.position)),20 * sin(GetAngleBetweenPoints(enemy[i].position,player.position))};
                    enemy[i].cooldown = 60;
                }

                if (enemy[i].health < 0){
                    enemy.erase(enemy.begin() + i);
                }else{
                    enemy.at(i).Draw(player.position);
                    bar.Draw({float(GetScreenWidth() / 2.f + (enemy[i].position.x - player.position.x)), float(GetScreenHeight() / 2.f + (enemy[i].position.y - player.position.y))},enemy[i].maxHealth,enemy[i].health);
                    //float(GetScreenWidth() / 2.f - 16 * 4) + (hitbox.x - playerPos.x)
                }

            }

            for(int i = 0; i < projectile.size(); i++){
                
                if (projectile[i].ttl>0){
                    projectile[i].Move();
                }else if (projectile[i].ttl > -10){
                    projectile[i].projImage = LoadTexture("resources/explosion_1.png");
                }else if (projectile[i].ttl > -20){
                    projectile[i].projImage = LoadTexture("resources/explosion_2.png");
                }else if (projectile[i].ttl > -40){
                    projectile[i].projImage = LoadTexture("resources/explosion_3.png");
                }else if (projectile[i].ttl > -50){
                    projectile[i].projImage = LoadTexture("resources/explosion_4.png");
                }

                if (FindDistance(player.position,projectile[i].position) < 50){
                    if (projectile[i].ttl > 0){ projectile[i].ttl = 0;}
                    if (projectile[i].ttl % 10 == 0) {
                        player.health-=projectile[i].damage;
                        player.position += {20 * cos(GetAngleBetweenPoints(projectile[i].position,player.position)),20 * sin(GetAngleBetweenPoints(projectile[i].position,player.position))};
                    }
                }


                projectile[i].Draw(player.position);
                //DrawRectangleLines(float(GetScreenWidth() / 2.f) + (projectile[i].position.x - player.position.x), float(GetScreenHeight() / 2.f) + (projectile[i].position.y - player.position.y),50,50,RED);

                projectile[i].ttl--;
                if (projectile[i].ttl<-50){
                    projectile.erase(projectile.begin() + i);
                }


            }

            if (weapon == 0) {
                if (sword.cooldownFrame != 0){ sword.Slash();}
                
            }

       
        
            player.Draw();
            bar.Draw({float(GetScreenWidth() / 2.f ), float(GetScreenHeight() / 2.f)},player.maxHealth,player.health);
            DrawRectangleLines(float(GetScreenWidth() / 2.f - 16 * 4), float(GetScreenHeight() / 2.f - 16 * 4),player.hitbox.width,player.hitbox.height,RED);
            sword.Draw(player.rotation);
            DrawCircleLines(float(GetScreenWidth() / 2.f), float(GetScreenHeight() / 2.f),185,WHITE);
            
        }
        

        EndDrawing();
    }
    
    //UnloadTexture(playerUp);
    enemy.clear();
    projectile.clear();
    CloseWindow();

    return 0;
}
