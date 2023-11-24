// file_utils.c

#include "file_utils.h"

// Function implementation
FILE *safefopen(const char *path, const char *mode)
{
    FILE *fp = fopen(path, mode);
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return fp;
}

void safe_fclose(FILE *fp)
{
    if (fclose(fp) != 0)
    {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
}
