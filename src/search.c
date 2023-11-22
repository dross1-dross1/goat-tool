
// src/search.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "utils.h"

int search_files(const char* search_term, const char* filename) {
    // Check for missing filename or search term
    if (!filename || !search_term) {
        printf("Error: No search term or filename provided.\n");
        return -1;
    }

    FILE *file = open_file(filename, "r");
    if (!file) return -1;

    char buffer[1024];
    int line_number = 1, match_count = 0;
    while (read_line(file, buffer, sizeof(buffer))) {
        if (strstr(buffer, search_term) != NULL) {
            printf("Line %d: %s", line_number, buffer);
            match_count++;
        }
        line_number++;
    }

    if (match_count == 0) printf("No matches found for '%s'.\n", search_term);

    fclose(file);
    return match_count;
}
