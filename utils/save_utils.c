
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
    char* filename = safe_malloc(strlen(pc->name) + 12); // allocate enough space for "save_files/" prefix and null terminator
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

struct PlayerCharacter* load_character()
{
    // get the character name
    char filename[32];
    printf("What is the name of the character you want to load? ");
    fgets(filename, sizeof(filename), stdin);

    // Remove newline character
    filename[strcspn(filename, "\n")] = '\0';

    // check if there is already a file with the pc.name as the filename
    char* full_filename = safe_malloc(strlen(filename) + 12); // allocate enough space for "save_files/" prefix and null terminator
    sprintf(full_filename, "save_files/%s", filename);
    
    printf("current working directory: %s\n", getcwd(NULL, 0));

    printf("character will be loaded from %s\n", full_filename);
    int fd = open(full_filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    FILE* fp = fdopen(fd, "r");
    if (fp == NULL) {
        perror("fdopen");
        exit(EXIT_FAILURE);
    }

    char name[32];
    fgets(name, sizeof(name), fp);
    name[strlen(name) - 1] = '\0'; // remove newline character

    struct PlayerCharacter* pc = create_player_character(name);

    fscanf(fp, "%d", &pc->strength.attr_val);
    fscanf(fp, "%d", &pc->dexterity.attr_val);
    fscanf(fp, "%d", &pc->constitution.attr_val);
    fscanf(fp, "%d", &pc->intelligence.attr_val);
    fscanf(fp, "%d", &pc->wisdom.attr_val);
    fscanf(fp, "%d", &pc->charisma.attr_val);

    fclose(fp);

    return pc;
}