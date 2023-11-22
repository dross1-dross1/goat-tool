
// src/file_operations.c

#include "file_operations.h"
#include "utils.h"

void print_file_content(int num_files, const char** filenames) {
    for (int i = 0; i < num_files; i++) {
        const char* filename = filenames[i];

        if (!file_exists(filename)) {
            print_error("Error opening file");
            continue;
        }

        if (is_directory(filename)) {
            printf("Error: Cannot print a directory '%s'.\n", filename);
            continue;
        }

        FILE *file = open_file(filename, "r");
        if (!file) continue; // Error message already printed by open_file

        printf("--- Content of %s ---\n", filename);
        char buffer[1024];
        while (read_line(file, buffer, sizeof(buffer))) printf("%s", buffer);

        fclose(file);
    }
}

void print_size(const char* filename) {
    if (file_exists(filename) == 0) {
        printf("Error: File does not exist.\n");
        return;
    }

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
        if (!file_exists(input_files[i])) {
            printf("Error: File '%s' does not exist.\n", input_files[i]);
            fclose(outfile);
            return -1;
        }

        if (is_directory(input_files[i])) {
            printf("Error: Invalid file type for '%s'. It is a directory.\n", input_files[i]);
            fclose(outfile);
            return -1;
        }

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

    // Check if the source file exists and is not a directory
    if (!file_exists(source)) {
        printf("Error: Source file does not exist.\n");
        return -1;
    }

    if (is_directory(source)) {
        printf("Error: Source is a directory.\n");
        return -1;
    }

    // Check if the destination file already exists
    if (file_exists(destination)) {
        printf("Error: Destination file already exists.\n");
        return -1;
    }

    // Open the source file for reading
    FILE* src_file = open_file(source, "r");
    if (!src_file) return -1;

    // Open the destination file for writing
    FILE* dest_file = open_file(destination, "w");
    if (!dest_file) {
        fclose(src_file);
        print_error("Error opening destination file");
        return -1;
    }

    // Copy the content from source to destination
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), src_file) != NULL) {
        fputs(buffer, dest_file);
    }

    // Close both files
    fclose(src_file);
    fclose(dest_file);

    // Delete the source file
    if (remove(source) != 0) {
        print_error("Error deleting source file");
        return -1;
    }

    printf("File moved/renamed successfully.\n");
    return 0;
}
