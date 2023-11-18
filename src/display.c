
// src/display.c

#include <stdio.h>
#include "display.h"

void display_help() {
    printf("GoatTool Help and Usage Instructions\n");
    printf("------------------------------------\n");
    printf("-h : Display this help menu.\n");
    printf("-p [FILENAME] : Print the contents of a file.\n");
    printf("-s [FILENAME] : Search a file for a string.\n");
    printf("-z [FILENAME] : Print the size of a file.\n");
    printf("-m [OUTPUT_FILE] [INPUT_FILES...] : Merge multiple files.\n");
    printf("-c [FILENAME] : Compress a file into .goat format.\n");
    printf("-d [FILENAME] : Decompress a .goat file.\n");
    printf("-r [FILENAME] : Print file permissions.\n");
    printf("-v [SOURCE] [DESTINATION] : Move or rename a file.\n");
    printf("\nFor more information, refer to the USAGE.md document.\n");
}
