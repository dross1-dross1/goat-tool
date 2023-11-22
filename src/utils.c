
// src/utils.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

char* read_line(FILE* file, char* buffer, size_t buffer_size) {
    if (fgets(buffer, buffer_size, file) == NULL) return NULL;
    return buffer;
}

int file_exists(const char* filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0) ? 1 : 0;
}

int is_directory(const char* filename) {
    struct stat buffer;
    if (stat(filename, &buffer) != 0) return -1;
    return S_ISDIR(buffer.st_mode) ? 1 : 0;
}

void print_error() {
    switch (errno) {
        case ENOENT:
            printf("Error: File does not exist.\n");
            break;
        case EACCES:
            printf("Error: Access denied.\n");
            break;
        case EPERM:
            printf("Error: Operation not permitted.\n");
            break;
        case EEXIST:
            printf("Error: File already exists.\n");
            break;
        case ENOTDIR:
            printf("Error: Not a directory.\n");
            break;
        case EISDIR:
            printf("Error: Is a directory.\n");
            break;
        case ENAMETOOLONG:
            printf("Error: File name too long.\n");
            break;
        case ENOSPC:
            printf("Error: No space left on device.\n");
            break;
        case EROFS:
            printf("Error: Read-only file system.\n");
            break;
        case EIO:
            printf("Error: An I/O error occurred.\n");
            break;
        case EINTR:
            printf("Error: Operation interrupted.\n");
            break;
        case EINVAL:
            printf("Error: Invalid argument.\n");
            break;
        default:
            printf("Error accessing file");
            break;
    }
}

FILE* open_file(const char* filename, const char* mode) {
    if (file_exists(filename) != 1 && strcmp(mode, "w") != 0) {
        printf("Error: Cannot access '%s' because it does not exist.\n", filename);
        return NULL;
    }
    if (is_directory(filename) == 1) {
        printf("Error: Cannot access '%s' because it is a directory.\n", filename);
        return NULL;
    }
    FILE* file = fopen(filename, mode);
    if (!file && errno == EACCES) printf("Error: Cannot access '%s' due to insufficient permissions.\n", filename);
    else if (!file) print_error();
    return file;
}
