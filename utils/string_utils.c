#include "string_utils.h"

#include <string.h>
#include <ctype.h>

#include "memory_utils.h"

const char Y = 'Y';
const char N = 'N';

void strip_newline_end(char* str)
{
   
    // find the last newline character
    char* newline = strrchr(str, '\n');

    // if newline is found, overwrite it with a null terminator
    if (newline != NULL)
    {
        *newline = '\0';
    }
}

void toUpperCase(char* name)
{
    

    // convert name to all uppercase
    for (int i = 0; i < strlen(name); i++) 
    {
        name[i] = toupper(name[i]);
    }
        
}

char* toUpperCaseCopy(char* str)
{
    // allocate memory for the new string
    char* result = safe_malloc(strlen(str) + 1);

    // copy the string
    strcpy(result, str);
    toUpperCase(result);
    // return the new string
    return result;
}

void toLowerCase(char* str)
{
    // convert name to all uppercase
    for (int i = 0; i < strlen(str); i++) 
    {
        str[i] = tolower(str[i]);
    }
}
char* toLowerCaseCopy(char* str)
{
    // allocate memory for the new string
    char* result = safe_malloc(strlen(str) + 1);

    // copy the string
    strcpy(result, str);
    toLowerCase(result);
    // return the new string
    return result;
}

