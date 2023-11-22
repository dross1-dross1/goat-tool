
// src/search.c

// Include necessary header files for functionality and custom utility functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "utils.h"

// Function to search a file for a specific term and print lines containing that term
int search_files(const char* search_term, const char* filename) {
    // Open the file for reading. If the file does not exist or cannot be opened, return -1
    FILE* file = open_file(filename, "r");
    if (!file) return -1;

    // Buffer to store each line read from the file
    char buffer[1024];

    // Variable to keep track of the current line number
    // Counter for the number of lines that contain the search term
    int line_number = 1, match_count = 0;

    // Read each line from the file and check for the search term
    while (read_line(file, buffer, sizeof(buffer))) {
        // Check if the current line contains the search term
        if (strstr(buffer, search_term) != NULL) {
            // If search term is found, print the line and its number
            printf("Line %d: %s", line_number, buffer);
            match_count++; // Increment the match counter
        }
        line_number++; // Move to the next line number
    }

    // After checking all lines, if no match is found, print a message
    if (match_count == 0) {
        printf("No matches found for '%s'.\n", search_term);
    }

    // Close the file after processing
    fclose(file);
    return 0; // Return 0 to indicate successful execution
}
