#pragma once
#include <string>
#include "raylib.h"

class Projectile{
public:
    Texture2D projImage;
    int damage;
    Vector2 position;
    float direction;
    float speed;
    int ttl;
    int team;
    Projectile(Texture2D img, int dam, Vector2 pos,float dir, float spe,int t,int tm){
        position =pos;
        damage=dam;
        projImage=img;
        direction=dir;
        speed=spe;
        ttl=t;
        team=tm;
    }

    

    
    void Draw(Vector2 playerPos) {
        DrawTextureEx(projImage, {float(GetScreenWidth() / 2.f - 16 * 4) + (position.x - playerPos.x), float(GetScreenHeight() / 2.f - 16 * 4) + (position.y - playerPos.y)} , 0, 4.f, WHITE);
    }
    
    void Move(){
        position += {speed * cos(direction),speed * sin(direction)};
    }
};
