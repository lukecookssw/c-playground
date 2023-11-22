
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "save_utils.h"

#include "memory_utils.h"
#include "string_utils.h"
#include "../character/player_character.h"

void save_character(struct PlayerCharacter* pc)
{
    char save_dir[] = "save_files/";
    char* character_file = toLowerCaseCopy(pc->name);
    int allocSize = sizeof(save_dir) + strlen(character_file); // using sizeof() includes the null-terminator so no need for +1
    
    // check if there is already a file with the pc.name as the filename
    char* full_filepath = safe_malloc(allocSize);
    sprintf(full_filepath, "%s%s", save_dir, character_file);
    
    printf("character will be saved in %s\n", full_filepath);
    int fd = open(full_filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); // open file for writing, create if it doesn't exist, truncate if it does
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

    printf("Save successful!\n");
}

struct PlayerCharacter* load_character()
{
    char save_dir[] = "save_files/";
    
    // get the character name
    char character_file[32];
    printf("Character name: ");
    fgets(character_file, sizeof(character_file), stdin);
    character_file[strcspn(character_file, "\n")] = '\0'; // Remove newline character
    toLowerCase(character_file); // lower case the filename
    
    // get the full file path
    int allocSize = sizeof(save_dir) + strlen(character_file);
    char* full_filepath = safe_malloc(allocSize);
    sprintf(full_filepath, "%s%s", save_dir, character_file);

    printf("Looking for %s\n", full_filepath);
    
    // open the file
    int fd = open(full_filepath, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    FILE* fp = fdopen(fd, "r");
    if (fp == NULL) {
        perror("fdopen");
        exit(EXIT_FAILURE);
    }
    struct PlayerCharacter* pc = create_player_character(character_file);

    
    fscanf(fp, "%d", &pc->strength.attr_val);
    fscanf(fp, "%d", &pc->dexterity.attr_val);
    fscanf(fp, "%d", &pc->constitution.attr_val);
    fscanf(fp, "%d", &pc->intelligence.attr_val);
    fscanf(fp, "%d", &pc->wisdom.attr_val);
    fscanf(fp, "%d", &pc->charisma.attr_val);

    fclose(fp);

    return pc;
}