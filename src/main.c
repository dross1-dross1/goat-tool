
// src/main.c

#include <stdio.h>
#include <string.h>
#include "display.h"
#include "file_operations.h"
#include "search.h"
#include "compression.h"
#include "permissions.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Error: Insuffecient argument count. Use -h for help.\n");
        return -1;
    }
    if (strcmp(argv[1], "-h") == 0) display_help();
    else if (strcmp(argv[1], "-p") == 0 && argc > 2) return print_file_content(argc - 2, (const char**)&argv[2]);
    else if (strcmp(argv[1], "-s") == 0 && argc == 4) return search_files(argv[2], argv[3]);
    else if (strcmp(argv[1], "-z") == 0 && argc == 3) return print_size(argv[2]);
    else if (strcmp(argv[1], "-m") == 0 && argc > 3) return merge_file(argv[2], argc - 3, (const char**)&argv[3]);
    else if (strcmp(argv[1], "-c") == 0 && argc == 3) return compress_goat(argv[2]);
    else if (strcmp(argv[1], "-d") == 0 && argc == 3) return decompress_goat(argv[2]);
    else if (strcmp(argv[1], "-r") == 0 && argc == 3) return print_file_permissions(argv[2]);
    else if (strcmp(argv[1], "-v") == 0 && argc == 4) return move_file(argv[2], argv[3]);
    else {
        printf("Error: Invalid command switch or missing arguments. Use -h for help.\n");
        return -1;
    }
    return 0;
}
