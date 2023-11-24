// string_utils.h

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

extern const char Y;
extern const char N;

// Function declaration
void toUpperCase(char* str);
char* toUpperCaseCopy(char* str);
void toLowerCase(char* str);
char* toLowerCaseCopy(char* str);
void strip_newline_end(char* str);

#endif // MEMORY_UTILS_H
