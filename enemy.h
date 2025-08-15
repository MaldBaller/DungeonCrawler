#pragma once
#include "character.h"
#include <cmath>
#include "raymath.h"



float GetAngleBetweenPoints(Vector2 a, Vector2 b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;

    return atan2f(dy, dx);  // Convert radians to degrees
}

float FindDistance(Vector2 position1, Vector2 position2) {
    // This is the Pythagorean Theorem
    return sqrt(pow(position1.x - position2.x, 2) + pow(position1.y - position2.y, 2));
}

class Enemy : public Character {
public:
    Texture2D sheet[4];
   
    int type; // 0 is melee 1 is range
    int cooldown = 360;
    int damage;
    int move = 0;
    int soundCooldown = 0;
    Enemy(Vector2 pos, Rectangle hit, Texture2D tex, float hp, int typ, int dmg,float spd)
    : Character(pos, hit, tex)
    {
        health = hp;
        maxHealth = hp;
        type = typ;
        damage = dmg;
        speed = spd;
        std::string buffer;
        
        for (int i = 0; i < 4; i++){
            if (type == 1) {
                buffer = "resources/wizard_" + std::to_string(i) + ".png";
            }
            else if (type == 0) {
                buffer = "resources/slime_" + std::to_string(i) + ".png";
            }
            else if (type == 2) {
                buffer = "resources/slime1_" + std::to_string(i) + ".png";
            }
            else if (type == 3) {
                buffer = "resources/slime2_" + std::to_string(i) + ".png";
            }
            else if (type == 4) {
                buffer = "resources/healer_" + std::to_string(i) + ".png";
            }
            else if (type == 5) {
                buffer = "resources/summon_" + std::to_string(i) + ".png";
            }
            else if (type == 6) {
                buffer = "resources/slime3_" + std::to_string(i) + ".png";
            }
            else if (type == 7) {
                buffer = "resources/slime4_" + std::to_string(i) + ".png";
            }
            sheet[i] = LoadTexture(buffer.c_str());
        }
    }
    
    // void Draw() {
    //     DrawTexture(texture, position.x, position.y, WHITE);
    // }
    
    void Move(float deltaX, float deltaY) {
        SetPosition({position.x + deltaX, position.y + deltaY});
        hitbox.x = position.x;
        hitbox.y = position.y;
    }

    void FollowPlayer(Vector2 playerPosition) {
        //const int stepDistance = speed;
        //speed *= 10;
        const Vector2 positionChanges[4] = {{0, speed * 10}, {0, -speed * 10}, {speed * 10, 0}, {-speed * 10, 0}};
        if (soundCooldown > 0) { soundCooldown--;}
        if (move > 0) { move--;}

        Vector2 moveToMake = {0, 0};
        for(int i = 0; i < 4; i++) {
            // iterates through possible moves to find the best one
            if(FindDistance( Vector2Add(position, positionChanges[i]) , playerPosition) < FindDistance( Vector2Add(position, moveToMake) , playerPosition)){
                moveToMake = positionChanges[i];
                playerImage = sheet[i];

            }
        }
        if (FindDistance(playerPosition,position) > 450 || (type != 1 && type != 4 && type != 5)) {
            Move(moveToMake.x / 10.f, moveToMake.y / 10.f);
            if ((type == 0 || type == 2 || type == 3|| type == 6 || type == 7) && FindDistance(playerPosition,position) < 90 && cooldown == 0){
                cooldown = -1;
            }

        }else{
            if (cooldown == 0){
                cooldown = -1;
            }
        }

        
    }
    // void FollowPlayer(Vector2 playerPosition) {
    //     float angleToPlayer = GetAngleBetweenPoints(position, playerPosition);
    //     Move(cos(angleToPlayer) * speed, sin(angleToPlayer) * speed);
    // }

    void Draw(Vector2 playerPos) {
        DrawTextureEx(playerImage, {float(GetScreenWidth() / 2.f - 16 * 4) + (position.x - playerPos.x), float(GetScreenHeight() / 2.f - 16 * 4) + (position.y - playerPos.y)}, 0.f, 4.f, WHITE);
        /*if (cooldown == 0){
            //DrawRectangleLines(float(GetScreenWidth() / 2.f - 16 * 4) + (hitbox.x - playerPos.x), float(GetScreenHeight() / 2.f - 16 * 4) + (hitbox.y - playerPos.y),hitbox.width,hitbox.height,BLUE);
        }*/
    }
};
