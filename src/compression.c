
// src/compression.c

#define _POSIX_C_SOURCE 200809L
#include "compression.h"
#include "utils.h"
#include <string.h>
#include <ctype.h>
#include <pthread.h>

char* compress_string(const char* str) {
    if (str == NULL) return NULL;
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
    char* decompressed = malloc(4 * strlen(str) + 1);
    if (decompressed == NULL) return NULL;
    int count;
    int j = 0;
    for (int i = 0; str[i] != '\0'; ) {
        if (isalpha(str[i]) && isdigit(str[i + 1])) {
            sscanf(&str[i + 1], "%d", &count);
            for (int k = 0; k < count; k++, j++) {
                if (j >= 10 * strlen(str)) break;
                decompressed[j] = str[i];
            }
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
    FILE* file = open_file(filename, "r");
    if (!file) return -1;
    FILE* outFile = open_file(output_filename, "w");
    if (!outFile) {
        fclose(file);
        return -1;
    }
    char buffer[1024];
    long line_num = 0;
    pthread_t threads[1024];
    LineData line_data[1024];
    while (read_line(file, buffer, sizeof(buffer))) {
        line_data[line_num].line = strdup(buffer);
        line_data[line_num].line_num = line_num;
        pthread_create(&threads[line_num], NULL, process_line, &line_data[line_num]);
        line_num++;
        if (line_num >= 1024) {
            printf("Error: Maximum thread count exceeded.\n");
            break;
        }
    }
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
    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s.goat", filename);
    return process_file(filename, output_filename, compress_line);
}

int decompress_goat(const char* filename) {
    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s.decompressed", filename);
    return process_file(filename, output_filename, decompress_line);
}
