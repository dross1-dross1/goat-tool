
// src/compression.c

// This directive defines the feature test macro _POSIX_C_SOURCE
// Setting _POSIX_C_SOURCE to 200809L specifies that the program
// wants to use POSIX.1-2008 compatible features.
// This ensures that the compiler exposes definitions conforming
// to the POSIX.1-2008 standard (also known as POSIX.1-2001 with
// revisions from POSIX.1-2004 and POSIX.1-2008).
// It is often used to ensure consistent behavior across different
// systems, especially for functions related to file handling,
// multi-threading, and other system interfaces.
#define _POSIX_C_SOURCE 200809L

// Include necessary header files
#include "compression.h"
#include "utils.h"
#include <string.h>
#include <ctype.h>
#include <pthread.h> // For multithreading

// Function to compress a string
char* compress_string(const char* str) {
    if (str == NULL) return NULL; // Return NULL if the input string is NULL

    // Allocate memory for the compressed string
    char* compressed = malloc(2 * strlen(str) + 1);
    if (compressed == NULL) return NULL; // Return NULL if memory allocation fails

    int count = 1; // Initialize count of consecutive characters
    int j = 0; // Index for the compressed string

    // Iterate through each character in the input string
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i]) && str[i] == str[i + 1]) {
            // Increment count if consecutive characters are the same
            count++;
        } else {
            // Compress the current character and its count into the compressed string
            if (isalpha(str[i])) j += sprintf(&compressed[j], "%c%d", str[i], count);
            else compressed[j++] = str[i]; // Copy non-alphabetic characters as is
            count = 1; // Reset count
        }
    }
    compressed[j] = '\0'; // Null-terminate the compressed string
    return compressed; // Return the compressed string
}

// Function to decompress a string
char* decompress_string(const char* str) {
    if (str == NULL) return NULL; // Return NULL if the input string is NULL

    // Allocate memory for the decompressed string
    char* decompressed = malloc(4 * strlen(str) + 1);
    if (decompressed == NULL) return NULL; // Return NULL if memory allocation fails

    int count; // To store the count of characters
    int j = 0; // Index for the decompressed string

    // Iterate through each character in the input string
    for (int i = 0; str[i] != '\0'; ) {
        if (isalpha(str[i]) && isdigit(str[i + 1])) {
            // Read the count of the current character
            sscanf(&str[i + 1], "%d", &count);

            // Append the character 'count' times to the decompressed string
            for (int k = 0; k < count; k++, j++) {
                if (j >= 10 * strlen(str)) break; // Avoid buffer overflow
                decompressed[j] = str[i];
            }
            // Move past the count in the input string
            while (isdigit(str[i + 1])) i++;
        } else {
            // Copy non-alphabetic characters as is
            decompressed[j++] = str[i];
        }
        i++; // Move to the next character
    }
    decompressed[j] = '\0'; // Null-terminate the decompressed string
    return decompressed; // Return the decompressed string
}

// Structures and functions to handle line compression and decompression using threads
typedef struct {
    char* line;
    long line_num;
} LineData;

void* compress_line(void* arg) {
    LineData* data = (LineData*) arg;
    data->line = compress_string(data->line);
    return NULL;
}

void* decompress_line(void* arg) {
    LineData* data = (LineData*) arg;
    data->line = decompress_string(data->line);
    return NULL;
}

// Function to process a file (compress or decompress) line by line using multithreading
int process_file(const char* filename, const char* output_filename, void* (*process_line)(void*)) {
    FILE* file = open_file(filename, "r");
    if (!file) return -1; // Return -1 if the file can't be opened

    FILE* out_file = open_file(output_filename, "w");
    if (!out_file) {
        fclose(file); // Close the input file if output file opening fails
        return -1;
    }

    char buffer[1024]; // Buffer to read lines from the file
    long line_num = 0; // Line number counter
    pthread_t threads[1024]; // Array of thread identifiers
    LineData line_data[1024]; // Array of line data for threads

    // Read each line and start a thread for processing that line
    while (read_line(file, buffer, sizeof(buffer))) {
        line_data[line_num].line = strdup(buffer); // Duplicate the line
        line_data[line_num].line_num = line_num; // Assign line number
        pthread_create(&threads[line_num], NULL, process_line, &line_data[line_num]); // Create a thread
        line_num++;
        if (line_num >= 1024) {
            printf("Error: Maximum thread count exceeded.\n");
            break;
        }
    }

    // Join all threads and write their output to the file
    for (long i = 0; i < line_num; i++) {
        pthread_join(threads[i], NULL); // Wait for thread completion
        fputs(line_data[i].line, out_file); // Write processed line to file
        free(line_data[i].line); // Free the duplicated line
    }

    // Close both the input and output files
    fclose(file);
    fclose(out_file);
    printf("File processed to %s.\n", output_filename); // Inform about file processing
    return 0;
}

// Functions to handle compression and decompression of files with the custom format
int compress_goat(const char* filename) {
    char output_filename[256]; // Buffer for output filename
    snprintf(output_filename, sizeof(output_filename), "%s.goat", filename); // Create output filename
    return process_file(filename, output_filename, compress_line); // Process file for compression
}

int decompress_goat(const char* filename) {
    char output_filename[256]; // Buffer for output filename
    snprintf(output_filename, sizeof(output_filename), "%s.decompressed", filename); // Create output filename
    return process_file(filename, output_filename, decompress_line); // Process file for decompression
}
