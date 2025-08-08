#pragma once
#include <string>
#include "raylib.h"

using namespace std;


class Projectile{
public:
    Texture2D projImage;
    int damage;
    Vector2 projPos;

    Projectile(Texture2D img, int dam, Vector2 pos){
        projPos=pos;
        damage=dam;
        projImage=img;
    }

    

    
    void Draw() {
        DrawTexture(projImage, projPos.x, projPos.y, WHITE);
    }
    
    void Update(int speed, string direction){
        if (direction=="right"){
            projPos.x+=speed;
        }
    else if (direction=="left"){
            projPos.x-=speed; 
        }
    else if (direction=="up"){
            projPos.y+=speed; 
        }
    else if (direction=="down"){
            projPos.y-=speed; 
        }
    }
};
