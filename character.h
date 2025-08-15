// character.h
#pragma once
#include "raylib.h"
#include <string>

class Character {
public:
    
    Vector2 position;
    Rectangle hitbox;
    float rotation = 0.f;
    Texture2D playerImage;
    int frame = 0;
    int maxFrame = 60;
    bool isWalking = false;

    //Atributes
    float speed;
    float health;
    float maxHealth;
    float stammina;
    float maxStamina;
    float mana;
    float maxMana;

    Character(Vector2 pos, Rectangle hit, Texture2D texture)
    {
        position = pos;
        hitbox = hit;
        playerImage = texture;
        speed = 2.0f;
        hitbox.x = position.x;
        hitbox.y = position.y;
        
    }

    void SetPosition(Vector2 pos){
        position = pos;
    }
    /*
    virtual void Draw(){
        DrawTexture(playerImage, position.x, position.y, WHITE);
    }*/
};
