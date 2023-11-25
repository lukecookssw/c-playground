// save_utils.h

#ifndef SAVE_UTILS_H
#define SAVE_UTILS_H

#include "../character/player_character.h"

void save_character(struct PlayerCharacter **pc);
void quicksave_character(struct PlayerCharacter **pc);
FILE *load_file(char *file_name);

//struct PlayerCharacter *old_load_character();

#endif // SAVE_UTILS_H