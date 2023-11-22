
// src/permissions.c

#include "permissions.h"
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

int print_file_permissions(const char* filename) {
    struct stat st;
    if (stat(filename, &st) == -1) {
        if (errno == ENOENT) printf("Error: File '%s' does not exist.\n", filename);
        else if (errno == EACCES) printf("Error: Permission denied for file '%s'.\n", filename);
        else perror("Error getting file permissions");
        return -1;
    }
    int perm = ((st.st_mode & S_IRUSR) ? 0400 : 0) |
               ((st.st_mode & S_IWUSR) ? 0200 : 0) |
               ((st.st_mode & S_IXUSR) ? 0100 : 0) |
               ((st.st_mode & S_IRGRP) ? 0040 : 0) |
               ((st.st_mode & S_IWGRP) ? 0020 : 0) |
               ((st.st_mode & S_IXGRP) ? 0010 : 0) |
               ((st.st_mode & S_IROTH) ? 0004 : 0) |
               ((st.st_mode & S_IWOTH) ? 0002 : 0) |
               ((st.st_mode & S_IXOTH) ? 0001 : 0);
    printf("Permissions for '%s': %03o\n", filename, perm);
    return 0;
}
