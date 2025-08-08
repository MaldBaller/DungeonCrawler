#pragma once
#include "character.h"
#include <cmath>
#include "raymath.h"


float GetAngleBetweenPoints(Vector2 a, Vector2 b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;

    return atan2f(dy, dx);  // Convert radians to degrees
}

float FindDistance(Vector2 position1, Vector2 position2) {
    // This is the Pythagorean Theorem
    return sqrt(pow(position1.x - position2.x, 2) + pow(position1.y - position2.y, 2));
}

class Enemy : public Character {
public:
    Enemy(Vector2 pos, Rectangle hit, Texture2D tex)
    : Character(pos, hit, tex)
    {

    }
    
    // void Draw() {
    //     DrawTexture(texture, position.x, position.y, WHITE);
    // }
    
    void Move(int deltaX, int deltaY) {
        SetPosition({position.x + deltaX, position.y + deltaY});
    }

    void FollowPlayer(Vector2 playerPosition) {
        const float speed = 1.0;
        float angleToPlayer = GetAngleBetweenPoints(position, playerPosition);
        Move(cos(angleToPlayer) * speed, sin(angleToPlayer) * speed);
    }

    void Draw(Vector2 playerPos) {
        DrawTextureEx(playerImage, {float(GetScreenWidth() / 2.f - 16 * 4) + (position.x - playerPos.x), float(GetScreenHeight() / 2.f - 16 * 4) + (position.y - playerPos.y)}, 0.f, 4.f, WHITE);
    }
};