// main.c
#include <stdio.h>
#include <string.h>
#include "display.h"
#include "file_operations.h"
#include "search_and_compression.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: No command switch provided. Use -h for help.\n");
        return 1;
    }

    char* operation = argv[1];

    if (strcmp(operation, "-h") == 0) {
        // Operation 1: Display the help menu
        display_help();
    } else if (strcmp(operation, "-p") == 0) {
        // Operation 2: Print the contents of a file
        if (argc < 3) {
            printf("Error: No filename provided.\n");
            return 1;
        }
        const char* filename = argv[2];
        // Call function to print file contents
        // Example: print_file_content(filename);
    } else if (strcmp(operation, "-s") == 0) {
        // Operation 3: Search a file for a string
        if (argc < 4) {
            printf("Error: No search term or filename provided.\n");
            return 1;
        }
        const char* search_term = argv[2];
        const char* filename = argv[3];
        // Call function to search for a string in a file
        // Example: search_files(filename, search_term);
    } else if (strcmp(operation, "-z") == 0) {
        // Operation 4: Print the size of a file
        if (argc < 3) {
            printf("Error: No filename provided.\n");
            return 1;
        }
        const char* filename = argv[2];
        // Call function to print the size of a file
        // Example: print_file_size(filename);
    } else if (strcmp(operation, "-m") == 0) {
        // Operation 5: Merge multiple files
        if (argc < 4) {
            printf("Error: No output or input files provided.\n");
            return 1;
        }
        const char* output_file = argv[2];
        // Call function to merge files
        // Example: merge_files(output_file, argv + 3, argc - 3);
    } else if (strcmp(operation, "-c") == 0) {
        // Operation 6: Compress a file into .goat format
        if (argc < 3) {
            printf("Error: No filename provided.\n");
            return 1;
        }
        const char* filename = argv[2];
        // Call function to compress a file
        // Example: compress_goat(filename);
    } else if (strcmp(operation, "-d") == 0) {
        // Operation 7: Decompress a .goat file
        if (argc < 3) {
            printf("Error: No filename provided.\n");
            return 1;
        }
        const char* filename = argv[2];
        // Call function to decompress a .goat file
        // Example: decompress_goat(filename);
    } else if (strcmp(operation, "-r") == 0) {
        // Operation 8: Print file permissions
        if (argc < 3) {
            printf("Error: No filename provided.\n");
            return 1;
        }
        const char* filename = argv[2];
        // Call function to print file permissions
        // Example: print_file_permissions(filename);
    } else if (strcmp(operation, "-v") == 0) {
        // Operation 9: Move or rename a file
        if (argc < 4) {
            printf("Error: No source or destination provided.\n");
            return 1;
        }
        const char* source = argv[2];
        const char* destination = argv[3];
        // Call function to move or rename a file
        // Example: move_or_rename_file(source, destination);
    } else {
        printf("Error: Unrecognized command switch: %s. Use -h for help.\n", operation);
        return 1;
    }

    return 0;
}
