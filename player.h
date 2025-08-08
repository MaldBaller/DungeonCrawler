// player.h
#pragma once
#include "character.h"
#include "item.h"
#include <vector>

class Player : public Character {
public:
    int experience;
    int gold;
    std::vector<Item> inventory;

    Player(Vector2 pos, Rectangle hit, Texture2D tex)
        : Character(pos, hit, tex)
    {
        experience = 0;
        gold = 0;
    }

    void Draw() override {
        DrawTextureEx(playerImage, {float(GetScreenWidth() / 2.f - 16 * 4), float(GetScreenHeight() / 2.f - 16 * 4)}, 0.f, 4.f, WHITE);
    }
};
