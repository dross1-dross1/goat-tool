
// include/utils.h

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>  // For FILE type
#include <stdlib.h> // For size_t type

FILE* open_file(const char* filename, const char* mode);
char* safe_strcat(char* dest, const char* src, size_t dest_size);
char* read_line(FILE* file, char* buffer, size_t buffer_size);
int file_exists(const char* filename);
int is_directory(const char* filename);
void print_error(const char* message);

#endif // UTILS_H
