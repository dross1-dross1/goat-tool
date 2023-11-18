
// src/main.c

#include <stdio.h>
#include <string.h>
#include "display.h"
#include "file_operations.h"
#include "search.h"
#include "compression.h"
#include "permissions.h"
// #include "utils.h"

int main(int argc, char **argv) {
    // Check if any arguments are provided
    if (argc < 2) {
        printf("Error: No command switch provided. Use -h for help.\n");
        return 1;
    }

    // Handle command switches
    if (strcmp(argv[1], "-h") == 0) {
        display_help();
    }
    else if (strcmp(argv[1], "-p") == 0 && argc == 3) {
        print_file_content(argv[2]);
    }
    else if (strcmp(argv[1], "-s") == 0 && argc == 4) {
        search_files(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "-z") == 0 && argc == 3) {
        print_size(argv[2]);  // Print the size of the file specified in bytes
    }
    else if (strcmp(argv[1], "-m") == 0 && argc > 3) {
        if (merge_file(argv[2], argc - 3, (const char**)&argv[3]) == 0) printf("Files merged successfully.\n");
        else printf("Error merging files.\n");
    }
    else if (strcmp(argv[1], "-c") == 0 && argc == 3) {
        compress_goat(argv[2]);
    }
    else if (strcmp(argv[1], "-d") == 0 && argc == 3) {
        decompress_goat(argv[2]);
    }
    else if (strcmp(argv[1], "-r") == 0 && argc == 3) {
        print_file_permissions(argv[2]);
    }
    else if (strcmp(argv[1], "-v") == 0 && argc == 4) {
        if (move_file(argv[2], argv[3])) printf("File moved/renamed successfully.\n");
        else printf("Error moving/renaming file.\n");
    }
    else {
        printf("Error: Invalid command switch or missing arguments. Use -h for help.\n");
    }

    return 0;
}
