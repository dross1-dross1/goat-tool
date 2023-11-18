// file_operations.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "file_operations.h"

// Function definitions
int create_file(const char* filename) {
FILE* file = fopen(filename, "w");  // Open file in write mode
    if (file == NULL) {
        perror("Error creating file");
        return 1;  // Return non-zero for failure
    }

    // Optional: You can write some initial content to the file if needed
    fprintf(file, "This is a newly created file.\n");

    fclose(file);  // Close the file
    return 0;      // Return zero for success
}

int delete_file(const char* filename) {
    int status = remove(filename);  // Use the remove function to delete the file

    if (status == 0) {
        printf("File \"%s\" deleted successfully.\n", filename);
        return 0;  // Return zero for success
    } else {
        perror("Error deleting file");
        return 1;  // Return non-zero for failure
    }
}

int copy_file(const char* source, const char* destination) {
    FILE* source_file = fopen(source, "rb");  // Open the source file in read-binary mode
    if (source_file == NULL) {
        perror("Error opening source file");
        return 1;  // Return non-zero for failure
    }

    FILE* destination_file = fopen(destination, "wb");  // Open the destination file in write-binary mode
    if (destination_file == NULL) {
        perror("Error opening destination file");
        fclose(source_file);  // Close the source file before returning
        return 1;            // Return non-zero for failure
    }

    int ch;  // Variable to store each character read from the source file

    // Copy each character from the source file to the destination file
    while ((ch = fgetc(source_file)) != EOF) {
        if (fputc(ch, destination_file) == EOF) {
            perror("Error writing to destination file");
            fclose(source_file);
            fclose(destination_file);
            return 1;  // Return non-zero for failure
        }
    }

    // Close both files
    fclose(source_file);
    fclose(destination_file);

    printf("File \"%s\" copied to \"%s\" successfully.\n", source, destination);
    return 0;  // Return zero for success
}

int move_file(const char* source, const char* destination) {
    int status = rename(source, destination);

    if (status == 0) {
        printf("File \"%s\" moved/renamed to \"%s\" successfully.\n", source, destination);
        return 0;  // Return zero for success
    } else {
        perror("Error moving/renaming file");
        return 1;  // Return non-zero for failure
    }
}

