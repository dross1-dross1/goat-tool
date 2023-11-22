
// src/compression.c

#define _POSIX_C_SOURCE 200809L
#include "compression.h"
#include "utils.h"
#include <string.h>
#include <ctype.h>
#include <pthread.h>

char* compress_string(const char* str) {
    if (str == NULL) return NULL;

    // Allocate memory for the compressed string
    char* compressed = malloc(2 * strlen(str) + 1);
    if (compressed == NULL) return NULL;

    int count = 1;
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i]) && str[i] == str[i + 1]) count++;
        else {
            if (isalpha(str[i])) j += sprintf(&compressed[j], "%c%d", str[i], count);
            else compressed[j++] = str[i];
            count = 1;
        }
    }

    compressed[j] = '\0';
    return compressed;
}

char* decompress_string(const char* str) {
    if (str == NULL) return NULL;

    // Estimate the maximum size needed for the decompressed string.
    // As a conservative estimate, use 10 times the length of the compressed string.
    char* decompressed = malloc(10 * strlen(str) + 1);
    if (decompressed == NULL) return NULL;

    int count;
    int j = 0;
    for (int i = 0; str[i] != '\0'; ) {
        if (isalpha(str[i]) && isdigit(str[i + 1])) {
            // Read the count after the character
            sscanf(&str[i + 1], "%d", &count);
            for (int k = 0; k < count; k++, j++) {
                if (j >= 10 * strlen(str)) break;
                decompressed[j] = str[i];
            }

            // Move the index i past the digits
            while (isdigit(str[i + 1])) i++;
        } else decompressed[j++] = str[i];
        i++;
    }

    decompressed[j] = '\0';
    return decompressed;
}


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

int process_file(const char* filename, const char* output_filename, void* (*process_line)(void*)) {
    if (!filename || !output_filename) {
        printf("Error: Invalid filename provided.\n");
        return -1;
    }

    FILE* file = open_file(filename, "r");
    if (!file) return -1;

    FILE* outFile = open_file(output_filename, "w");
    if (!outFile) {
        fclose(file);
        return -1;
    }

    char buffer[1024];
    long line_num = 0;
    pthread_t threads[1024];  // Adjust thread array size as needed
    LineData line_data[1024]; // Adjust line data array size as needed

    while (read_line(file, buffer, sizeof(buffer))) {
        line_data[line_num].line = strdup(buffer);
        line_data[line_num].line_num = line_num;
        pthread_create(&threads[line_num], NULL, process_line, &line_data[line_num]);
        line_num++;

        // Check for max thread count
        if (line_num >= 1024) {
            printf("Error: Maximum thread count exceeded.\n");
            break;
        }
    }

    // Join threads and write output in order
    for (long i = 0; i < line_num; i++) {
        pthread_join(threads[i], NULL);
        fputs(line_data[i].line, outFile);
        free(line_data[i].line);
    }

    fclose(file);
    fclose(outFile);
    printf("File processed to %s.\n", output_filename);

    return 0;
}

int compress_goat(const char* filename) {
    if (!filename) {
        printf("Error: Invalid filename provided.\n");
        return -1;
    }

    if (!file_exists(filename)) {
        printf("Error: File does not exist.\n");
        return -1;
    }

    if (is_directory(filename)) {
        printf("Error: Cannot compress a directory.\n");
        return -1;
    }

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s.goat", filename);
    return process_file(filename, output_filename, compress_line);
}

int decompress_goat(const char* filename) {
    if (!filename) {
        printf("Error: Invalid filename provided.\n");
        return -1;
    }

    if (!file_exists(filename)) {
        printf("Error: File does not exist.\n");
        return -1;
    }

    if (is_directory(filename)) {
        printf("Error: Cannot decompress a directory.\n");
        return -1;
    }

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s.decompressed", filename);
    return process_file(filename, output_filename, decompress_line);
}
