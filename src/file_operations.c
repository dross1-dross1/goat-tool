
// src/file_operations.c

#include "file_operations.h"
#include "utils.h"

void print_file_content(const char* filename) {
    if (!file_exists(filename)) {
        print_error("Error opening file");
        return;
    }

    if (is_directory(filename)) {
        printf("Error: Cannot print a directory.\n");
        return;
    }

    FILE *file = open_file(filename, "r");
    if (!file) return; // Error message already printed by open_file

    char buffer[1024];
    while (read_line(file, buffer, sizeof(buffer))) printf("%s", buffer);

    fclose(file);
}

void print_size(const char* filename) {
    if (is_directory(filename)) {
        printf("Error: Cannot get the size of a directory.\n");
        return;
    }

    FILE* file = open_file(filename, "r");
    if (!file) return; // Error message already printed by open_file

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    printf("Size: %ld bytes.\n", size);
}

int merge_file(const char* output_file, int num_files, const char** input_files) {
    if (num_files < 2) {
        printf("Error: At least two input files are required.\n");
        return -1;
    }

    FILE* outfile = open_file(output_file, "w");
    if (!outfile) return -1; // Error message already printed by open_file

    for (int i = 0; i < num_files; i++) {
        FILE* infile = open_file(input_files[i], "r");
        if (!infile) {
            fclose(outfile);
            return -1; // Error message already printed by open_file
        }

        char buffer[1024];
        while (read_line(infile, buffer, sizeof(buffer))) fputs(buffer, outfile);

        fclose(infile);
    }

    fclose(outfile);
    printf("Files merged successfully into '%s'.\n", output_file);
    return 0;
}

int move_file(const char* source, const char* destination) {
    if (source == NULL || destination == NULL) {
        printf("Error: No source or destination provided.\n");
        return -1;
    }

    if (!file_exists(source)) {
        printf("Error: Source file does not exist.\n");
        return -1;
    }

    if (rename(source, destination) != 0) {
        print_error("Error moving/renaming file");
        return -1;
    }

    printf("File moved/renamed successfully.\n");
    return 0;
}
