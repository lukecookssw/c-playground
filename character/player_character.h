#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "attribute.h"

struct PlayerCharacter
{
    char name[32];
    int level;

    // TODO: Change these to an array of attributes
    struct Attribute strength;
    struct Attribute dexterity;
    struct Attribute constitution;
    struct Attribute intelligence;
    struct Attribute wisdom;
    struct Attribute charisma;
};

// functions
struct PlayerCharacter* create_player_character(char* name);


#endif // PLAYER_CHARACTER_H
