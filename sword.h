#pragma once
#include "raylib.h"

class Sword {
public:
    Texture2D swordImage;
    int damage;
    Vector2 position = {0, 0};

    Sword(Texture2D texture, int dmg) {
        swordImage = texture;
        damage = dmg;
    }
};