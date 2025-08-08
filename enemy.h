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
    Enemy(Vector2 pos, Rectangle hit, Texture2D tex, float hp)
    : Character(pos, hit, tex)
    {
        health = hp;
    }
    
    // void Draw() {
    //     DrawTexture(texture, position.x, position.y, WHITE);
    // }
    
    void Move(int deltaX, int deltaY) {
        SetPosition({position.x + deltaX, position.y + deltaY});
        hitbox.x = position.x;
        hitbox.y = position.y;
    }

    void FollowPlayer(Vector2 playerPosition) {
        const int stepDistance = 1;
        const Vector2 positionChanges[4] = {{0, stepDistance}, {0, -stepDistance}, {stepDistance, 0}, {-stepDistance, 0}};

        Vector2 moveToMake = {0, 0};
        for(int i; i < 4; i++) {
            // iterates through possible moves to find the best one
            if(FindDistance( Vector2Add(position, positionChanges[i]) , playerPosition) < FindDistance( Vector2Add(position, moveToMake) , playerPosition)){
                moveToMake = positionChanges[i];
            }
        }
        Move(moveToMake.x, moveToMake.y);
    }
    // void FollowPlayer(Vector2 playerPosition) {
    //     float angleToPlayer = GetAngleBetweenPoints(position, playerPosition);
    //     Move(cos(angleToPlayer) * speed, sin(angleToPlayer) * speed);
    // }

    void Draw(Vector2 playerPos) {
        DrawTextureEx(playerImage, {float(GetScreenWidth() / 2.f - 16 * 4) + (position.x - playerPos.x), float(GetScreenHeight() / 2.f - 16 * 4) + (position.y - playerPos.y)}, 0.f, 4.f, WHITE);
        DrawRectangleLines(float(GetScreenWidth() / 2.f - 16 * 4) + (hitbox.x - playerPos.x), float(GetScreenHeight() / 2.f - 16 * 4) + (hitbox.y - playerPos.y),hitbox.width,hitbox.height,BLUE);
    }
};