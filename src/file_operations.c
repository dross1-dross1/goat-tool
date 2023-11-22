
// src/file_operations.c

#include "file_operations.h"
#include "utils.h"

int print_file_content(int num_files, const char** filenames) {
    for (int i = 0; i < num_files; i++) {
        const char* filename = filenames[i];
        FILE *file = open_file(filename, "r");
        if (!file) continue;
        printf("--- Content of '%s' ---\n", filename);
        char buffer[1024];
        while (read_line(file, buffer, sizeof(buffer))) printf("%s", buffer);
        fclose(file);
    }
    return 0;
}

int print_size(const char* filename) {
    FILE* file = open_file(filename, "r");
    if (!file) return -1;
    fseek(file, 0, SEEK_END);
    printf("Size: %ld bytes.\n", ftell(file));
    fclose(file);
    return 0;
}

int merge_file(const char* output_file, int num_files, const char** input_files) {
    FILE* outfile = open_file(output_file, "w");
    if (!outfile) return -1;
    for (int i = 0; i < num_files; i++) {
        FILE* infile = open_file(input_files[i], "r");
        if (!infile) {
            fclose(outfile);
            return -1;
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
    FILE* src_file = open_file(source, "r");
    if (!src_file) return -1;
    FILE* dest_file = open_file(destination, "w");
    if (!dest_file) {
        fclose(src_file);
        return -1;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), src_file) != NULL) fputs(buffer, dest_file);
    fclose(src_file);
    fclose(dest_file);
    if (remove(source) != 0) {
        printf("Error: Unable to delete source file.");
        return -1;
    }
    printf("File moved/renamed successfully.\n");
    return 0;
}
