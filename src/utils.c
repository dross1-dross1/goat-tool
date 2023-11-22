
// src/utils.c

// Include necessary header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h> // For file status
#include <errno.h>    // For error numbers

// Function to read a line from a file
char* read_line(FILE* file, char* buffer, size_t buffer_size) {
    // fgets reads a line from the specified stream into the buffer
    // It reads at most one less than the size of buffer
    // Returns NULL if no characters were read
    if (fgets(buffer, buffer_size, file) == NULL) return NULL;
    return buffer; // Return the buffer containing the line
}

// Function to check if a file exists
int file_exists(const char* filename) {
    struct stat buffer;
    // stat returns 0 if successful (file exists)
    return (stat(filename, &buffer) == 0) ? 1 : 0;
}

// Function to check if a filename is a directory
int is_directory(const char* filename) {
    struct stat buffer;
    // If stat fails (return non-zero), return -1
    if (stat(filename, &buffer) != 0) return -1;
    // S_ISDIR macro checks if the file is a directory
    return S_ISDIR(buffer.st_mode) ? 1 : 0;
}

// Function to print an error message based on the global errno
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

// Function to open a file with a given mode
FILE* open_file(const char* filename, const char* mode) {
    // If file does not exist and mode is not 'w', return NULL
    if (file_exists(filename) != 1 && strcmp(mode, "w") != 0) {
        printf("Error: Cannot access '%s' because it does not exist.\n", filename);
        return NULL;
    }
    // If the filename is a directory, return NULL
    if (is_directory(filename) == 1) {
        printf("Error: Cannot access '%s' because it is a directory.\n", filename);
        return NULL;
    }
    // Attempt to open the file with the specified mode
    FILE* file = fopen(filename, mode);
    // Handle file access errors
    if (!file && errno == EACCES)
        printf("Error: Cannot access '%s' due to insufficient permissions.\n", filename);
    else if (!file)
        print_error();
    return file; // Return the file pointer
}
