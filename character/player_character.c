// player_character.c

#include <string.h>

#include "../utils/memory_utils.h"
#include "../utils/string_utils.h"

#include "player_character.h"

struct PlayerCharacter* create_player_character(char* name)
{
    // allocate the memory
    struct PlayerCharacter* pc = safe_malloc(sizeof(struct PlayerCharacter));

    // set the name
    strcpy(pc->name, toUpperCaseCopy(name));
}

void free_player_character(struct PlayerCharacter* pc)
{
    // free the memory
    free(pc);
}