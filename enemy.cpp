#include "character.cpp"

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
};