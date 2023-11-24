#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../character/player_character.h"
#include "../utils/save_utils.h"
#include "command_map.h"

void handle_list(struct PlayerCharacter* pc)
{
    // list all the command names
    int i = 0;
    printf("Available commands:\n");
    while (command_handlers[i].name != NULL)
    {
        printf("%s\n", command_handlers[i].name);
        i++;
    }
}

// Define the command handlers
void handle_save(struct PlayerCharacter* pc) {
    quicksave_character(pc);
}

void handle_exit(struct PlayerCharacter* pc) {
    save_character(pc);
    exit(0);
}

void handle_attributes(struct  PlayerCharacter *pc)
{
    
    printf("Strength:       %d\n", pc->strength.attr_val);
    printf("Dexterity:      %d\n", pc->dexterity.attr_val);
    printf("Constitution:   %d\n", pc->constitution.attr_val);
    printf("Intelligence:   %d\n", pc->intelligence.attr_val);
    printf("Wisdom:         %d\n", pc->wisdom.attr_val);
    printf("Charisma:       %d\n", pc->charisma.attr_val);
}


// Define the command handlers
CommandHandler command_handlers[] = {
    { "list", handle_list },
    { "save", handle_save },
    { "stats", handle_attributes },
    { "attributes", handle_attributes },
    { "exit", handle_exit },
    { NULL, NULL }
};