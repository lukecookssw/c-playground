
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "save_utils.h"

#include "memory_utils.h"
#include "../character/player_character.h"

void save_character(struct PlayerCharacter* pc)
{
    // check if there is already a file with the pc.name as the filename
    char* filename = safe_malloc(strlen(pc->name) + 10); // allocate enough space for "/dnd/" prefix and null terminator
    sprintf(filename, "save_files/%s", pc->name);
    
    printf("character will be saved in %s\n", filename);
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); // open file for writing, create if it doesn't exist, truncate if it does
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    FILE* fp = fdopen(fd, "w"); // convert file descriptor to FILE*
    if (fp == NULL) {
        perror("fdopen");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%d\n", pc->strength.attr_val);
    fprintf(fp, "%d\n", pc->dexterity.attr_val);
    fprintf(fp, "%d\n", pc->constitution.attr_val);
    fprintf(fp, "%d\n", pc->intelligence.attr_val);
    fprintf(fp, "%d\n", pc->wisdom.attr_val);
    fprintf(fp, "%d\n", pc->charisma.attr_val);
    fclose(fp);
}