// player_character.c

#include <string.h>

#include "../utils/memory_utils.h"
#include "../utils/string_utils.h"

#include "player_character.h"
#include "item.h"

struct PlayerCharacter* create_player_character(char* name)
{
    // allocate the memory
    struct PlayerCharacter* pc = safe_malloc(sizeof(struct PlayerCharacter));
    
    // set the name
    strcpy(pc->name, toUpperCaseCopy(name));
    
    // new up some inventory space
    pc->ptr_inventory = safe_malloc(10 * sizeof(struct Item));
    
    
}

void free_player_character(struct PlayerCharacter* pc)
{
    // free the inventory
    free(pc->ptr_inventory);

    // free the character
    free(pc);
}