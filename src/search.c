
// src/search.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

void search_files(const char* filename, const char* search_term) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char buffer[1024];
    int line_number = 1;
    int found = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, search_term) != NULL) {
            printf("Line %d: %s", line_number, buffer);
            found = 1;
        }
        line_number++;
    }

    if (!found) {
        printf("No matches found.\n");
    }

    fclose(file);
}
