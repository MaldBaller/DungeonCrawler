// tile.h
#pragma once
#include "raylib.h"

const char * textureList[15] {
    "resources/missingtexture.png",
    "resources/dirt_floor.png",
    "resources/right_wall.png",
    "resources/bottom_wall.png",
    "resources/left_wall.png",
    "resources/top_wall.png",
    "resources/top_right_corner_wall.png",
    "resources/bottom_right_corner_wall.png",
    "resources/bottom_left_corner_wall.png",
    "resources/top_left_corner_wall.png",
    "resources/top_right_square.png",
    "resources/bottom_right_square.png",
    "resources/bottom_left_square.png",
    "resources/top_left_square.png",
    "resources/tile_14.png"
};

class Tile {
public:
    Texture2D tileImage;
    int tileNumber;
    Vector2 position;

    Tile(int num, Vector2 pos) {
        tileNumber = num;
        position = pos;
        tileImage = LoadTexture(textureList[tileNumber]);
    }

    void Draw(Vector2 playerPos) {
        DrawTextureEx(tileImage, {
            float(GetScreenWidth() / 2.f - 16 * 4) + (position.x * (32*4) - playerPos.x), 
            float(GetScreenHeight() / 2.f - 16 * 4) + (position.y * (32*4) - playerPos.y)
        }, 0.f, 4.f, WHITE);
    }
};