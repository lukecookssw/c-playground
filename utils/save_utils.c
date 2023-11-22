
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


int confirm_save()
{
    char save[3]; // buffer to hold the input

    while (1)
    {
        // ask the user if they want to save
        printf("Would you like to save your character? (Y/n) ");
        fgets(save, sizeof(save), stdin);
        toUpperCase(save);

        // evaluate response
        if (save[0] == '\n' || save[0] == Y)
        {
            // Save the character
            return 1;
        }
        else if (save[0] == N)
        {
            // User entered 'y' or 'n'
            return 0;
        }
        else
        {
            // Invalid input, ask again
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        }
    }
}

void quicksave_character(struct PlayerCharacter *pc)
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


void save_character(struct PlayerCharacter* pc)
{
    int save = confirm_save();
    if (!save) {
        return;
    }
    quicksave_character(pc);
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

    int attr_val;
    fscanf(fp, "%d", &attr_val);
    updateAttribute(&pc->strength, attr_val);

    // important:
    // pc is a pointer
    // pc->strength is a struct
    // &pc->strength is a pointer to a struct. Read it like this: &(ptr->struct_member)


    fscanf(fp, "%d", &attr_val);
    updateAttribute(&pc->dexterity, attr_val);

    fscanf(fp, "%d", &attr_val);
    updateAttribute(&pc->constitution, attr_val);

    fscanf(fp, "%d", &attr_val);
    updateAttribute(&pc->intelligence, attr_val);

    fscanf(fp, "%d", &attr_val);
    updateAttribute(&pc->wisdom, attr_val);

    fscanf(fp, "%d", &attr_val);
    updateAttribute(&pc->charisma, attr_val);

    fclose(fp);

    return pc;
}