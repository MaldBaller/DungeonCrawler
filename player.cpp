#include "character.cpp"
#include "item.cpp"

class player : public character {
private:
    int experience; 
    int gold;

    item inventory[100];
    

    
public:
     
    player(int str, int sta, int itl, int dex, int team, int lvl, int weg, std::string nam , Vector2 pos, Rectangle hit = {0, 0, 0, 0}, Texture2D tex, float rot = 0.0f, float scl = 1.0f, int exper) 
     : character(str, sta, itl, dex, team, lvl, weg, nam, pos, hit, tex, rot, scl)
    {
        experience = 0;
    }

};