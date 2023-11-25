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

void updateAttribute(struct Attribute *attribute, unsigned short val)
{
    if (attribute == NULL)
    {
        printf("attribute is null\n");
        return;
    }
    // update the value
    attribute->attr_val = val;

    // calculate the modifier
    calculateModifier(attribute);
}