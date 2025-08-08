// character.h
#pragma once
#include "raylib.h"
#include <string>

class Character {
public:
    float speed;
    Vector2 position;
    Rectangle hitbox;
    float rotation = 0.f;
    Texture2D playerImage;

    Character(Vector2 pos, Rectangle hit, Texture2D texture)
    {
        position = pos;
        hitbox = hit;
        playerImage = texture;
        speed = 2.0f;
    }

    void SetPosition(Vector2 pos){
        position = pos;
    }
    /*
    virtual void Draw(){
        DrawTexture(playerImage, position.x, position.y, WHITE);
    }*/
};
