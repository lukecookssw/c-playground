// file_utils.h

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdlib.h>
#include <stdio.h>

// Function declaration
FILE *safe_fopen(const char *path, const char *mode);
void safe_fclose(FILE *fp);

#endif // FILE_UTILS_H
