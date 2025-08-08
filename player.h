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

    Player(Vector2 pos, Rectangle hit, Texture2D texture)
        : Character(pos, hit, texture)
    {
        experience = 0;
        gold = 0;
    }

    void Draw() override {
        DrawTexture(playerImage, position.x, position.y, WHITE);
    }
};
