
// src/file_operations.c

// Include the necessary header files
#include "file_operations.h"
#include "utils.h"

// Function to print the content of multiple files
int print_file_content(int num_files, const char** filenames) {
    // Loop through each file provided
    for (int i = 0; i < num_files; i++) {
        // Get the current filename from the array
        const char* filename = filenames[i];

        // Open the file for reading. If it fails, continue to the next file
        FILE* file = open_file(filename, "r");
        if (!file) continue;

        // Print the title for the file content
        printf("--- Content of '%s' ---\n", filename);

        // Create a buffer to hold each line of the file
        char buffer[1024];

        // Read each line of the file and print it
        while (read_line(file, buffer, sizeof(buffer))) printf("%s", buffer);

        // Close the file
        fclose(file);
    }
    // Return 0 to indicate successful execution
    return 0;
}

// Function to print the size of a file
int print_size(const char* filename) {
    // Open the file for reading
    FILE* file = open_file(filename, "r");
    if (!file) return -1; // Return -1 if file opening fails

    // Move the file pointer to the end of the file
    fseek(file, 0, SEEK_END);

    // Get the size of the file
    printf("Size: %ld bytes.\n", ftell(file));

    // Close the file
    fclose(file);

    // Return 0 to indicate success
    return 0;
}

// Function to merge multiple files into one
int merge_file(const char* output_file, int num_files, const char** input_files) {
    // Open the output file for writing
    FILE* outfile = open_file(output_file, "w");
    if (!outfile) return -1; // Return -1 if opening the output file fails

    // Loop through each input file
    for (int i = 0; i < num_files; i++) {
        // Open the current input file for reading
        FILE* infile = open_file(input_files[i], "r");
        if (!infile) {
            // Close the output file and return -1 if opening the input file fails
            fclose(outfile);
            return -1;
        }

        // Create a buffer to hold each line of the input file
        char buffer[1024];

        // Read each line of the input file and write it to the output file
        while (read_line(infile, buffer, sizeof(buffer))) fputs(buffer, outfile);

        // Close the input file
        fclose(infile);
    }

    // Close the output file
    fclose(outfile);

    // Print a success message
    printf("Files merged successfully into '%s'.\n", output_file);

    // Return 0 to indicate success
    return 0;
}

// Function to move or rename a file
int move_file(const char* source, const char* destination) {
    // Open the source file for reading
    FILE* src_file = open_file(source, "r");
    if (!src_file) return -1; // Return -1 if opening the source file fails

    // Open the destination file for writing
    FILE* dest_file = open_file(destination, "w");
    if (!dest_file) {
        // Close the source file and return -1 if opening the destination file fails
        fclose(src_file);
        return -1;
    }

    // Create a buffer to hold each line of the source file
    char buffer[1024];

    // Read each line from the source file and write it to the destination file
    while (fgets(buffer, sizeof(buffer), src_file) != NULL) fputs(buffer, dest_file);

    // Close both the source and destination files
    fclose(src_file);
    fclose(dest_file);

    // Delete the source file
    if (remove(source) != 0) {
        // Print an error message and return -1 if deleting the source file fails
        printf("Error: Unable to delete source file.");
        return -1;
    }

    // Print a success message
    printf("File moved/renamed successfully.\n");

    // Return 0 to indicate success
    return 0;
}
