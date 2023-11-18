
// src/file_operations.c

#include <stdio.h>
#include <stdlib.h>
#include "file_operations.h"

void print_file_content(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}

void print_size(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0, SEEK_END); // Seek to the end of the file
    long size = ftell(file);  // Get the current file pointer position, which is the file size
    fclose(file);

    printf("Size: %ld bytes\n", size);
}

int merge_file(const char* output_file, int num_files, const char** input_files) {
    FILE* outfile = fopen(output_file, "w");
    if (!outfile) {
        perror("Error opening output file");
        return -1;
    }

    for (int i = 0; i < num_files; i++) {
        FILE* infile = fopen(input_files[i], "r");
        if (!infile) {
            perror("Error opening input file");
            fclose(outfile);
            return -1;
        }

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), infile)) {
            fputs(buffer, outfile);
        }

        fclose(infile);
    }

    fclose(outfile);
    return 0;
}

int move_file(const char* source, const char* destination) {
    if (rename(source, destination) != 0) {
        perror("Error moving file");
        return -1;
    }
    return 0;
}
