#include "raylib.h"

class character {
public:
    // Basic attributes
    int health;
    float speed;
    Vector2 position;
    Rectangle hitbox;
    Texture2D texture;
    float rotation;
    float scale;
    int team; // 0 for player, 1 for enemy, 2 for neutral
    int level; // Level of the character

    /* Attributes
        Defult value is 0, every level is +0.05 x 3 times (ex. damage = weapon damage * strength)
        Different stats scale diffenly respect to real stats
    */
    float strength;
    float stamina;
    float intelligence;
    float dexterity;
    
    // Constructor
    character(float strength, float stamina, float intelligence, float dexterity, int team)
    {
        int level = (strength + stamina + intelligence + dexterity - 4) * ;
    }
};