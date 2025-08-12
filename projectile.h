#pragma once
#include <string>
#include "raylib.h"

using namespace std;


class Projectile{
public:
    Texture2D projImage;
    int damage;
    Vector2 position;
    float direction;
    float speed;

    Projectile(Texture2D img, int dam, Vector2 pos){
        position =pos;
        damage=dam;
        projImage=img;
    }

    

    
    void Draw() {
        DrawTexture(projImage, position.x, position.y, WHITE);
    }
    
    void Move(float spe, float dir){
        direction = dir;
        speed = spe;
        position += {speed * cos(direction),speed * sin(direction)};
    }
};
