#include <stdio.h>
#include <stdlib.h>

#include "character/attribute.h"
#include "character/player_character.h"
#include "utils/save_utils.h"
#include "utils/string_utils.h"

void request_attr(char* attr_name, int* attr_val)
{
    printf("What is your character's %s score? ", attr_name);
    scanf("%d", attr_val);
}

void set_attributes(struct PlayerCharacter* pc, int scores[6])
{
    updateAttribute(&pc->strength, scores[0]);
    updateAttribute(&pc->dexterity, scores[1]);
    updateAttribute(&pc->constitution, scores[2]);
    updateAttribute(&pc->intelligence, scores[3]);
    updateAttribute(&pc->wisdom, scores[4]);
    updateAttribute(&pc->charisma, scores[5]);
}

struct PlayerCharacter* create_character_form()
{
    // ask the user to type in their character's name
    char name[32];
    printf("What is your character's name? ");
    scanf("%s", name);
    
    // get the attribute scores
    int attrs[6];
    request_attr("strength", &attrs[0]);
    request_attr("dexterity", &attrs[1]);
    request_attr("constitution", &attrs[2]);
    request_attr("intelligence", &attrs[3]);
    request_attr("wisdom", &attrs[4]);
    request_attr("charisma", &attrs[5]);

    // create the player character
    struct PlayerCharacter* pc = create_player_character(name);
    // update the attributes
    set_attributes(pc, attrs);

    return pc;
}

void print_character(struct PlayerCharacter* pc)
{
    printf("Name: %s\n", pc->name);
    printf("Attribute\tScore\tModifier\n");
    printf("Strength\t%d\t%c%d\n", pc->strength.attr_val, pc->strength.attr_mod >= 0 ? '+' : '-', abs(pc->strength.attr_mod));
    printf("Dexterity\t%d\t%c%d\n", pc->dexterity.attr_val, pc->dexterity.attr_mod >= 0 ? '+' : '-', abs(pc->dexterity.attr_mod));
    printf("Constitution\t%d\t%c%d\n", pc->constitution.attr_val, pc->constitution.attr_mod >= 0 ? '+' : '-', abs(pc->constitution.attr_mod));
    printf("Intelligence\t%d\t%c%d\n", pc->intelligence.attr_val, pc->intelligence.attr_mod >= 0 ? '+' : '-', abs(pc->intelligence.attr_mod));
    printf("Wisdom\t\t%d\t%c%d\n", pc->wisdom.attr_val, pc->wisdom.attr_mod >= 0 ? '+' : '-', abs(pc->wisdom.attr_mod));
    printf("Charisma\t%d\t%c%d\n", pc->charisma.attr_val, pc->charisma.attr_mod >= 0 ? '+' : '-', abs(pc->charisma.attr_mod));
}

char request_save(struct PlayerCharacter* pc)
{
    printf("Would you like to save your character? (y/n) ");
    char save;
    scanf(" %c", &save);
    
    return save;
}

int main() {
    
    struct PlayerCharacter* pc = create_character_form();
    
    print_character(pc);
    char save;
    save = request_save(pc);
    
    if (save == 'y') {
        // save the character
        save_character(pc);
    }
    return 0;
}
