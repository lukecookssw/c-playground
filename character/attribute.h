// attribute.h

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

struct Attribute
{
    unsigned short attr_val;
    unsigned short attr_mod;
};

// Function declarations
void updateAttribute(struct Attribute *attribute, unsigned short val);

#endif // ATTRIBUTE_H
