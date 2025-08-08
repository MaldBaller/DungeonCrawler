// sword.h
#pragma once
#include "raylib.h"
#include "enemy.h"
#include <vector>

class Sword {
public:
    Texture2D swordImage;
    float damage;
    Vector2 position = {0, 0};

    Sword(Texture2D texture, float dmg) {
        swordImage = texture;
        damage = dmg;
    }

    void Draw() {
        DrawTexture(swordImage, position.x, position.y, WHITE);
    }

    void Update(Vector2 playerPostion) {
        position = playerPostion;
    }

    void Slash(std::vector <Enemy> enemy) { // The list of enemies is in main, so the function needs to take it in
        for(int i; i < enemy.size(); i++) {
            if(enemy[i].position.x - position.x < 60 && enemy[i].position.y - position.y < 60) {
                // TODO: damage enemy when health is implemented
            }
        }
    }
};