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
    while (command_handlers[i].name != NULL)
    {
        printf("%s\n", command_handlers[i].name);
        i++;
    }
}

// Define the command handlers
void handle_save(struct PlayerCharacter* pc) {
    save_character(pc);
}

void handle_exit(struct PlayerCharacter* pc) {
    exit(0);
}


// Define the command handlers
CommandHandler command_handlers[] = {
    { "list", handle_list },
    { "save", handle_save },
    { "exit", handle_exit },
    { NULL, NULL }
};