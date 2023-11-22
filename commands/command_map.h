
#ifndef COMMAND_MAP_H
#define COMMAND_MAP_H

#include <stddef.h>
#include "../character/player_character.h"

// Define a struct for the command handlers
typedef struct {
    const char *name;
    void (*handler)(struct PlayerCharacter*);
} CommandHandler;

// Declare the command_handlers array
extern CommandHandler command_handlers[];

// Function declarations
void handle_list(struct PlayerCharacter* pc);
void handle_save(struct PlayerCharacter* pc);
void handle_exit(struct PlayerCharacter* pc);

#endif // COMMAND_MAP_H
