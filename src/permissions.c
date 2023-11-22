
// src/permissions.c

// Include necessary header files for functionality
#include "permissions.h"
#include <stdio.h>
#include <sys/stat.h> // For file status structures and stat function
#include <errno.h>    // For error codes

// Function to print the file permissions of a specified file
int print_file_permissions(const char* filename) {
    struct stat st; // Declare a structure to store file status information

    // Get file status. On error, check the type of error and print an appropriate message
    if (stat(filename, &st) == -1) {
        if (errno == ENOENT)
            printf("Error: File '%s' does not exist.\n", filename); // File not found
        else if (errno == EACCES)
            printf("Error: Permission denied for file '%s'.\n", filename); // Access denied
        else
            perror("Error getting file permissions"); // Other errors
        return -1;
    }

    // Calculate file permissions in octal format by checking each permission bit
    int perm = ((st.st_mode & S_IRUSR) ? 0400 : 0) | // User read permission
               ((st.st_mode & S_IWUSR) ? 0200 : 0) | // User write permission
               ((st.st_mode & S_IXUSR) ? 0100 : 0) | // User execute permission
               ((st.st_mode & S_IRGRP) ? 0040 : 0) | // Group read permission
               ((st.st_mode & S_IWGRP) ? 0020 : 0) | // Group write permission
               ((st.st_mode & S_IXGRP) ? 0010 : 0) | // Group execute permission
               ((st.st_mode & S_IROTH) ? 0004 : 0) | // Others read permission
               ((st.st_mode & S_IWOTH) ? 0002 : 0) | // Others write permission
               ((st.st_mode & S_IXOTH) ? 0001 : 0);  // Others execute permission

    // Print the permissions in octal format
    printf("Permissions for '%s': %03o\n", filename, perm);

    return 0; // Return 0 to indicate successful execution
}
