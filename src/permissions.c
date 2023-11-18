
// src/permissions.c

#include "permissions.h"
#include <stdio.h>
#include <sys/stat.h>

void print_file_permissions(const char* filename) {
    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Error getting file permissions");
        return;
    }

    printf("Permissions for '%s': ", filename);
    printf((st.st_mode & S_IRUSR) ? "r" : "-");
    printf((st.st_mode & S_IWUSR) ? "w" : "-");
    printf((st.st_mode & S_IXUSR) ? "x" : "-");
    printf((st.st_mode & S_IRGRP) ? "r" : "-");
    printf((st.st_mode & S_IWGRP) ? "w" : "-");
    printf((st.st_mode & S_IXGRP) ? "x" : "-");
    printf((st.st_mode & S_IROTH) ? "r" : "-");
    printf((st.st_mode & S_IWOTH) ? "w" : "-");
    printf((st.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

