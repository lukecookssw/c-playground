// attribute.h

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

struct Attribute {
    char attr_name[4]; // 1 more than the string length so it can hold the null terminator
    int attr_val;
    int attr_mod;
};

// Function declarations
struct Attribute *createAttribute();
void updateAttribute(struct Attribute *attribute, int val);

// Don't think I need this
//void freeAttribute(struct Attribute *attribute);


#endif // ATTRIBUTE_H
