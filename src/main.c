
// src/main.c

// Include necessary header files
#include <stdio.h>
#include <string.h>
#include "display.h"
#include "file_operations.h"
#include "search.h"
#include "compression.h"
#include "permissions.h"

// The main function: Entry point of the program
int main(int argc, char** argv) {
    // Check if the number of arguments is less than 2 (program name + at least one argument)
    if (argc < 2) {
        printf("Error: Insufficient argument count. Use -h for help.\n");
        return -1; // Return -1 to indicate an error
    }

    // Check if the first argument is "-h", and if so, display the help menu
    if (strcmp(argv[1], "-h") == 0) display_help();

    // Check if the first argument is "-p" and there are more than 2 arguments in total
    // Then call the function to print file contents
    else if (strcmp(argv[1], "-p") == 0 && argc > 2) return print_file_content(argc - 2, (const char**)&argv[2]);

    // Check if the first argument is "-s" and exactly 4 arguments are provided
    // Then call the function to search files
    else if (strcmp(argv[1], "-s") == 0 && argc == 4) return search_files(argv[2], argv[3]);

    // Check if the first argument is "-z" and exactly 3 arguments are provided
    // Then call the function to print file size
    else if (strcmp(argv[1], "-z") == 0 && argc == 3) return print_size(argv[2]);

    // Check if the first argument is "-m" and more than 3 arguments are provided
    // Then call the function to merge files
    else if (strcmp(argv[1], "-m") == 0 && argc > 3) return merge_file(argv[2], argc - 3, (const char**)&argv[3]);

    // Check if the first argument is "-c" and exactly 3 arguments are provided
    // Then call the function to compress a file
    else if (strcmp(argv[1], "-c") == 0 && argc == 3) return compress_goat(argv[2]);

    // Check if the first argument is "-d" and exactly 3 arguments are provided
    // Then call the function to decompress a file
    else if (strcmp(argv[1], "-d") == 0 && argc == 3) return decompress_goat(argv[2]);

    // Check if the first argument is "-r" and exactly 3 arguments are provided
    // Then call the function to print file permissions
    else if (strcmp(argv[1], "-r") == 0 && argc == 3) return print_file_permissions(argv[2]);

    // Check if the first argument is "-v" and exactly 4 arguments are provided
    // Then call the function to move or rename a file
    else if (strcmp(argv[1], "-v") == 0 && argc == 4) return move_file(argv[2], argv[3]);

    // If none of the above conditions are met, print an error message
    else {
        printf("Error: Invalid command switch or missing arguments. Use -h for help.\n");
        return -1; // Return -1 to indicate an error
    }

    // Return 0 to indicate successful execution
    return 0;
}
