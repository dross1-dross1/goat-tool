
// src/display.c

// Include necessary header files
#include <stdio.h>
#include "display.h" // Include the header file for display-related functions

// Function to display help and usage instructions
int display_help() {
    // Print the title of the help section
    printf("GoatTool Help and Usage Instructions\n");
    printf("------------------------------------\n");

    // Print instructions for each command supported by the tool
    printf("-h : Display this help menu.\n"); // Help menu
    printf("-p [FILENAMES...] : Print the contents of one or more files.\n"); // Print file contents
    printf("-s [SEARCH_TERM] [FILENAME] : Search a file for a string.\n"); // Search files for a term
    printf("-z [FILENAME] : Print the size of a file.\n"); // Print file size
    printf("-m [OUTPUT_FILE] [INPUT_FILES...] : Merge multiple files.\n"); // Merge multiple files
    printf("-c [FILENAME] : Compress a file into .goat format.\n"); // Compress a file
    printf("-d [FILENAME] : Decompress a .goat file.\n"); // Decompress a file
    printf("-r [FILENAME] : Print file permissions.\n"); // Print file permissions
    printf("-v [SOURCE] [DESTINATION] : Move or rename a file.\n"); // Move or rename a file

    // Return 0 to indicate successful execution of the function
    return 0;
}
