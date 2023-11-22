
// src/utils.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

void print_error(const char* message) {
    switch (errno) {
        case ENOENT:
            printf("Error: File does not exist.\n");
            break;
        case EACCES:
        case EPERM:
            printf("Error: Permission denied.\n");
            break;
        default:
            perror(message);
            break;
    }
}

FILE* open_file(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (!file) print_error("Error opening file");
    return file;
}

char* safe_strcat(char* dest, const char* src, size_t dest_size) {
    size_t dest_len = strlen(dest);
    size_t i;
    for (i = 0; i < dest_size - dest_len - 1 && src[i] != '\0'; i++) dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';
    return dest;
}

char* read_line(FILE* file, char* buffer, size_t buffer_size) {
    if (fgets(buffer, buffer_size, file) == NULL) return NULL;
    return buffer;
}

int file_exists(const char* filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

int is_directory(const char* filename) {
    struct stat buffer;
    if (stat(filename, &buffer) != 0) return -1;
    return S_ISDIR(buffer.st_mode);
}
