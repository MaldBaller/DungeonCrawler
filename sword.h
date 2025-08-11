// sword.h
#pragma once
#include "raylib.h"
#include "enemy.h"
#include <vector>
#include <iostream>
#include <string>

class Sword {
public:
    Texture2D swordImage;
    float damage;
    Vector2 position = {0, 0};
    bool isSlashing = false;
    int slashFrames = 15;
    int slashFrame = 0;
    int cooldownFrames = 120;
    int cooldownFrame = 0;

    Sword(Texture2D texture, float dmg) {
        swordImage = texture;
        damage = dmg;
    }

    void Draw(float rot) {
        if (cooldownFrame == -1) {
            DrawTexturePro(swordImage, {0,0,30,50} ,{ float(GetScreenWidth() / 2.f),float(GetScreenHeight() / 2.f),150,250}, {75,250}, rot - 60 + slashFrame * 8, WHITE);
        }
    }

    void Update(Vector2 playerPostion) {
        position = playerPostion;
    }

    void Slash(std::vector <Enemy> enemy, float playerDir) { // The list of enemies is in main, so the function needs to take it in
        //DrawText((std::to_string(cooldownFrame)).c_str(),20,0,90,WHITE);
        if (cooldownFrame > -1) { if (cooldownFrame > 0) { cooldownFrame--;} return;}
        
        slashFrame ++;
        for(int i; i < enemy.size(); i++) {
            if(enemy[i].position.x - position.x < 60 && enemy[i].position.y - position.y < 60) {
                enemy[i].health -= damage;
            }
        }
        if (slashFrame > slashFrames){
            slashFrame = 0;
            cooldownFrame = cooldownFrames;
        }

        //Draw(playerDir - 60 + slashFrame);
    }
};