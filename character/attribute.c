#include "attribute.h"
#include <stdlib.h>
#include <string.h>
#include "../utils/memory_utils.h"
#include "../utils/string_utils.h"

// private functions
static int calculateModifier(struct Attribute *attr)
{
    // calculate the modifier
    attr->attr_mod = (attr->attr_val - 10) / 2;
}

static void setName(struct Attribute* attr, char* name)
{
    // convert the name to uppercase
    toUpperCase(name);

    // set the name
    strcpy(attr->attr_name, name);
}

void updateAttribute(struct Attribute *attribute, int val)
{
    // update the value
    attribute->attr_val = val;

    // calculate the modifier
    calculateModifier(attribute);
}

struct Attribute* createAttribute(char* name, int val)
{
    // allocate the memory for the attribute
    struct Attribute* attr = safe_malloc(sizeof(struct Attribute));
    
    // set values
    setName(attr, name);
    updateAttribute(attr, val);
}

// void freeAttribute(struct Attribute *attribute)
// {
//     // free the memory
//     free(attribute);
// }
