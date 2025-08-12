// tile.h
#pragma once
#include "raylib.h"

class Tile {
public:
    Texture2D tileImage;
    int tileNumber;
    Vector2 position;

    Tile(int num, Vector2 pos) {
        tileNumber = num;
        position = pos;
    }

    void Draw(Vector2 playerPos) {
        DrawTextureEx(tileImage, {float(GetScreenWidth() / 2.f - 16 * 4) + (position.x * (32*4) - playerPos.x), float(GetScreenHeight() / 2.f - 16 * 4) + (position.y * (32*4) - playerPos.y)}, 0.f, 4.f, WHITE);
    }
};