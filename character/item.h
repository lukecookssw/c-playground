#ifndef ITEM_H
#define ITEM_H

typedef enum {
    HEAD,
    NECK,
    SHOULDERS, // for capes, etc.
    CHEST,
    FEET,
    WRISTS_HANDS,
    FINGER_ONE,
    FINGER_TWO,
    WEAPON,
    SHIELD,
    POTION,
    NO_SLOT // for items that don't go in a specific slot
} ItemSlot;


struct Item {
    char name[32];
    char description[128];
    int weight;
    int value;
    ItemSlot slot;
    int equipped;
};

// functions
struct Item* create_item(char* name, char* description, int weight, int value, ItemSlot slot);
void destroy_item(struct Item* item);

#endif // PLAYER_CHARACTER_H
