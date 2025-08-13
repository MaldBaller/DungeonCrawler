// sword.h
#pragma once
#include "raylib.h"
#include "enemy.h"
#include "player.h"
#include <vector>
#include <iostream>
#include <string>

class Sword {
public:
    Texture2D swordImage;
    float damage;
    //Vector2 position = {0, 0};
    bool isSlashing = false;
    int slashFrames = 15;
    int slashFrame = 0;
    int cooldownFrames = 90;
    int cooldownFrame = 0;
    Rectangle collider;

    Sword(Texture2D texture, float dmg) {
        swordImage = texture;
        damage = dmg;
    }

    void Draw(float rot) {
        if (cooldownFrame == -1) {
            DrawTexturePro(swordImage, {0,0,32,32} ,{ float(GetScreenWidth() / 2.f),float(GetScreenHeight() / 2.f),200,200}, {100,190}, rot - 60 + slashFrame * 8, WHITE);
        }
    }

    void Slash() { // The list of enemies is in main, so the function needs to take it in
        //DrawText((std::to_string(cooldownFrame)).c_str(),20,0,90,WHITE);
        if (cooldownFrame > -1) { if (cooldownFrame > 0) { cooldownFrame--;} return;}
        
        //collider = {player.position.x,player.position.y,40,}


        slashFrame ++;
        
        if (slashFrame > slashFrames){
            slashFrame = 0;
            cooldownFrame = cooldownFrames;
        }

        //Draw(playerDir - 60 + slashFrame);
    }

    void Parry() { // The list of enemies is in main, so the function needs to take it in
        //DrawText((std::to_string(cooldownFrame)).c_str(),20,0,90,WHITE);
        if (cooldownFrame > -1) { if (cooldownFrame > 0) { cooldownFrame--;} return;}
        
        //collider = {player.position.x,player.position.y,40,}


        slashFrame ++;
        
        if (slashFrame > slashFrames){
            slashFrame = 0;
            cooldownFrame = cooldownFrames;
        }

        //Draw(playerDir - 60 + slashFrame);
    }
};