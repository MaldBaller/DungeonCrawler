#include "character.cpp"
#include <cmath>
#include "raymath.h"

float FindDistance(Vector2 position1, Vector2 position2) {
    // This is the Pythagorean Theorem
    return sqrt(pow(position1.x - position2.x, 2) + pow(position1.y - position2.y, 2));
}

class enemy : public character {
public:
    enemy(          // Constructor
        int str,
        int sta,
        int itl,
        int dex,
        int team,
        int lvl,
        int weg,
        std::string nam,
        Vector2 pos = {0, 0},
        Rectangle hit = {0, 0, 0, 0},
        Texture2D tex = {},
        float rot = 0.0f,
        float scl = 1.0f
    )
    : character(str, sta, itl, dex, team, lvl, weg, nam, pos, hit, tex, rot, scl)
    {

    }
    
    void Draw() {
        DrawTexture(texture, position.x, position.y, WHITE);
    }

    void Move(int deltaX, int deltaY) {
        setPosition({position.x + deltaX, position.y + deltaY});
    }

    void FollowPlayer(Vector2 playerPosition) {
        const int stepDistance = 1;
        const Vector2 positionChanges[4] = {{0, stepDistance}, {0, -stepDistance}, {stepDistance, 0}, {-stepDistance, 0}};

        Vector2 moveToMake = {0, 0};
        for(int i; i < 4; i++) {
            // iterates through possible moves to find the best one
            if(FindDistance( Vector2Add(position, positionChanges[i]) , playerPosition) < FindDistance(position, playerPosition)){
                moveToMake = positionChanges[i];
            }
        }
    }
};