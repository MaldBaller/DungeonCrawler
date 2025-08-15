#include "character.h"
#include "player.h"
#include "enemy.h"
#include <vector>
#include <iostream>
#include "projectile.h"
#include <random>
#include "sword.h"
#include "health.h"
#include <chrono>
#include "score.h"

int randint(int min, int max) {
	return (rand() + rand()) % (max + 1 - min) + min;
}

int posneg(){
    if (randint(0,1)){
        return 1;
    }
    return -1;
}

using namespace std::chrono;

int main()
{
    srand(time(NULL));
    InitWindow(1600, 1000, "DungeonCrawler");
    //ToggleFullscreen();
    InitAudioDevice();
    //WriteScore(15);

    std::string buffer;


    Texture2D back = LoadTexture("resources/title.png");
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
    

    Sound sound[10];
    for (int i = 0; i < 6;i++){
        buffer = "resources/sound_" + std::to_string(i) + ".wav";
        sound[i] = LoadSound(buffer.c_str());
    }

    auto timeStart = steady_clock::now();
    auto time = steady_clock::now();
    int yellowTime = 0;
    bool toggle = false;
    //int seconds


    int enemiesKilled = 0;
    int damageDelt = 0; 
    int score = 0;
    int highScore = ReadScore();
    int wave = 0;
    int waveDisplay = 0;


    int screenX = GetScreenWidth();
    int screenY = GetScreenHeight();
    
    
    int gamemode = -1;
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
            //ToggleFullscreen();
            //screenX = GetScreenWidth();
            //screenY = GetScreenHeight();
        }

        time = steady_clock::now();

        // Movement
        if (gamemode == 1) {
            
            if (time - timeStart >= seconds{ 1 }) {
                timeStart = time;
                score += 10;
            }

            if (IsKeyPressed(KEY_TAB)){
                gamemode = 3;
            }

            //player.changeImage(playerDown);
            player.isWalking = false;
            if (player.frame > player.maxFrame) { player.frame = 0;}
            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
                player.position.y -= player.speed;
                playerDir = up;
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
            if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
                player.position.y += player.speed;
                playerDir = down;
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
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
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
            if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
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
                    if (sword.cooldownFrame == 0) { sword.cooldownFrame = -1; PlaySound(sound[0]);}
                }else{

                }
            }
            
            if (player.health > 0){
                player.health += 0.01;
                if (player.health > player.maxHealth){ player.health = player.maxHealth; }
            }else {
                gamemode  = 2;
                enemy.clear();
                projectile.clear();
                PlaySound(sound[2]);
            }
            
            if (enemy.size() == 0){
                waveDisplay = 240;
                wave++;
                PlaySound(sound[5]);

                for(int i = 0; i < 3 * (wave / 3 + 1); i++){
                    if (randint(0,2) == 0){
                        enemy.push_back(Enemy( {float(randint(900,500) * posneg()),float(randint(900,500) * posneg())}, {0,0,32*4,32*4}, LoadTexture("resources/slime.png"), 50.0, 1,30,1.2));
                    }
                    else{
                        enemy.push_back(Enemy( {float(randint(900,500) * posneg()),float(randint(900,500) * posneg())}, {0,0,32*4,32*4}, LoadTexture("resources/slime.png"), 100.0, 0,30,1.5));
                    }
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
                            score += sword.damage;
                            damageDelt += sword.damage;
                            if (enemy[i].soundCooldown == 0) {PlaySound(sound[1]); enemy[i].soundCooldown = 91;}
                            enemy[i].Move(10 * cos(GetAngleBetweenPoints(player.position,enemy[i].position)),10 * sin(GetAngleBetweenPoints(player.position,enemy[i].position)));
                        }
                    }
                }

                if (enemy[i].cooldown > 0){enemy[i].cooldown--;}
                if (enemy[i].cooldown == -1 && enemy[i].type == 1){
                    projectile.push_back(Projectile(LoadTexture("resources/mid_flame.png"),enemy[i].damage,enemy[i].position,GetAngleBetweenPoints(enemy[i].position,player.position),8,80,1));
                    enemy[i].cooldown = 600;
                }if (enemy[i].cooldown == -1 && enemy[i].type == 0){
                    player.health -= enemy[i].damage;
                    enemy[i].cooldown = 60;
                    enemy[i].move = 10;
                    PlaySound(sound[4]);
                }if (enemy[i].type == 0 && enemy[i].move > 0){
                    player.position += {4 * cos(GetAngleBetweenPoints(enemy[i].position,player.position)),4 * sin(GetAngleBetweenPoints(enemy[i].position,player.position))};
                }

                if (enemy[i].health < 0){
                    enemy.erase(enemy.begin() + i);
                    enemiesKilled++;
                    score += 200;
                    yellowTime = 120;
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
                    if (projectile[i].ttl % 20 == 0) {
                        player.health-=projectile[i].damage;
                        player.position += {20 * cos(GetAngleBetweenPoints(projectile[i].position,player.position)),20 * sin(GetAngleBetweenPoints(projectile[i].position,player.position))};
                    }
                }

                if (projectile[i].ttl == 0){ PlaySound(sound[3]); }
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
            //DrawRectangleLines(float(GetScreenWidth() / 2.f - 16 * 4), float(GetScreenHeight() / 2.f - 16 * 4),player.hitbox.width,player.hitbox.height,RED);
            sword.Draw(player.rotation);
            //DrawCircleLines(float(GetScreenWidth() / 2.f), float(GetScreenHeight() / 2.f),185,WHITE);
            
            buffer = "Score: " + std::to_string(score);
            if (yellowTime <= 0){
                DrawTextEx(GetFontDefault(),buffer.c_str(),{0,0},50,3,WHITE);
            }else{
                DrawTextEx(GetFontDefault(),buffer.c_str(),{0,0},50,3,YELLOW);
                yellowTime--;
            }

            buffer = "High Score: " + std::to_string(highScore);
            DrawText(buffer.c_str(), screenX - MeasureText(buffer.c_str(),50),0,50,YELLOW);
            buffer = "Wave: " + std::to_string(wave);
            DrawText(buffer.c_str(), screenX / 2.f - MeasureText(buffer.c_str(),50) / 2.f,0,50,RED);
            
            if (waveDisplay > 0){
                waveDisplay--;
                buffer = "Wave: " + std::to_string(wave);
                DrawText(buffer.c_str(), screenX / 2.f - MeasureText(buffer.c_str(),200) / 2.f,screenY / 2.f,200,RED);
            }
            
        }
        

        if (gamemode == 2){
            buffer = "You Died...";
            DrawText(buffer.c_str(), screenX / 2.f - MeasureText(buffer.c_str(),80) / 2.f,screenY / 2.f - 250 ,80,RED);
            buffer = "Mosters Killed: " + std::to_string(enemiesKilled);
            DrawText(buffer.c_str(), screenX / 2.f - MeasureText(buffer.c_str(),50) / 2.f,screenY / 2.f - 100,50,WHITE);
            buffer = "Wave: " + std::to_string(wave);
            DrawText(buffer.c_str(), screenX / 2.f - MeasureText(buffer.c_str(),50) / 2.f,screenY / 2.f ,50,WHITE);
            buffer = "Final Score: " + std::to_string(score);
            DrawText(buffer.c_str(), screenX / 2.f - MeasureText(buffer.c_str(),60) / 2.f,screenY / 2.f + 100,60,YELLOW);

            if (score < highScore){
                buffer = "High Score: " + std::to_string(highScore);
                DrawText(buffer.c_str(), screenX / 2.f - MeasureText(buffer.c_str(),60) / 2.f,screenY / 2.f + 200,60,YELLOW);
            }else{
                DrawText("New High Score!", screenX / 2.f - MeasureText("New High Score!",60) / 2.f,screenY / 2.f + 200,60,YELLOW);
            }

            if (time - timeStart >= seconds{ 1 }) {
                timeStart = time;
                toggle = !toggle;
            }if (toggle){
                DrawText("Press space to continue..", screenX / 2.f - MeasureText("Press space to continue..",50) / 2.f,screenY / 2.f + 350,50,WHITE);
                
            }

            if (IsKeyDown(KEY_SPACE)){
                gamemode = -1;
            }


        }

        if (gamemode == -1){
            gamemode = 0;
            enemy.clear();
            projectile.clear();
            enemiesKilled = 0;
            damageDelt = 0;
            wave = 0;
            
            for(int i = 0; i < 0; i++){
                enemy.push_back(Enemy( {float(randint(-900,900)),float(randint(-900,900))}, {0,0,32*4,32*4}, LoadTexture("resources/slime.png"), 50.0, 1,30,1.f));
                enemy.push_back(Enemy( {float(randint(-900,900)),float(randint(-900,900))}, {0,0,32*4,32*4}, LoadTexture("resources/slime.png"), 50.0, 0,30,1.5));
            }
            player = Player({0, 0}, {0,0,32*4,32*4}, playerUp,100);
            if (score > highScore){
                WriteScore(score);  
                highScore = score;
            }score = 0;
            toggle = false;
            timeStart = steady_clock::now();
        }

        if (gamemode == 0){
            DrawTexturePro(back,{0,0,172,99},{0,0,1600,1000},{0,0},0.f,WHITE);

            buffer = std::to_string(highScore);
            DrawTextEx(GetFontDefault(),buffer.c_str(),{float(screenX) - 260,130},40,3,BLACK);
            DrawTextEx(GetFontDefault(),"High Score:",{float(screenX) - 270,90},30,3,BLACK);

            if (time - timeStart >= seconds{ 1 }) {
                timeStart = time;
                toggle = true;
            }
            if (IsKeyDown(KEY_SPACE) && toggle){
                gamemode = 1;
            }
        }

        if (gamemode == 3){
            buffer = "Paused";
            DrawText(buffer.c_str(), screenX / 2.f - MeasureText(buffer.c_str(),80) / 2.f,screenY / 2.f - 250 ,80,RED);
            buffer = "Mosters Killed: " + std::to_string(enemiesKilled);
            DrawText(buffer.c_str(), screenX / 2.f - MeasureText(buffer.c_str(),50) / 2.f,screenY / 2.f - 100,50,WHITE);
            buffer = "Damage Dealt: " + std::to_string(damageDelt);
            DrawText(buffer.c_str(), screenX / 2.f - MeasureText(buffer.c_str(),50) / 2.f,screenY / 2.f ,50,WHITE);
            buffer = "Score: " + std::to_string(score);
            DrawText(buffer.c_str(), screenX / 2.f - MeasureText(buffer.c_str(),60) / 2.f,screenY / 2.f + 100,60,YELLOW);

            if (time - timeStart >= seconds{ 1 }) {
                timeStart = time;
                toggle = !toggle;
            }if (toggle){
                
                DrawText("Press space to continue..", screenX / 2.f - MeasureText("Press space to continue..",50) / 2.f,screenY / 2.f + 350,50,WHITE);
            }

            if (IsKeyDown(KEY_SPACE)){
                gamemode = 1;
            }
        }

        EndDrawing();
    }
    
    //UnloadTexture(playerUp);
    enemy.clear();
    projectile.clear();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
