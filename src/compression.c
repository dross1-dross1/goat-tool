
// src/compression.c

#include "compression.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compress_goat(const char* filename) {
    FILE* original = fopen(filename, "r");
    if (!original) {
        perror("Error opening original file");
        return -1;
    }

    char compressedFilename[256];
    snprintf(compressedFilename, sizeof(compressedFilename), "%s.goat", filename);
    FILE* compressed = fopen(compressedFilename, "w");
    if (!compressed) {
        perror("Error creating compressed file");
        fclose(original);
        return -1;
    }

    char currentChar, lastChar = fgetc(original);
    int count = 1;
    while ((currentChar = fgetc(original)) != EOF) {
        if (currentChar == lastChar) {
            count++;
        } else {
            fprintf(compressed, "%c%d", lastChar, count);
            count = 1;
        }
        lastChar = currentChar;
    }
    fprintf(compressed, "%c%d", lastChar, count); // write the last set

    fclose(original);
    fclose(compressed);
    printf("File compressed to %s\n", compressedFilename);
    return 0;
}

int decompress_goat(const char* filename) {
    FILE* compressed = fopen(filename, "r");
    if (!compressed) {
        perror("Error opening compressed file");
        return -1;
    }

    char decompressedFilename[256];
    snprintf(decompressedFilename, sizeof(decompressedFilename), "%s.decompressed", filename);
    FILE* decompressed = fopen(decompressedFilename, "w");
    if (!decompressed) {
        perror("Error creating decompressed file");
        fclose(compressed);
        return -1;
    }

    char ch;
    int count;
    while (fscanf(compressed, "%c%d", &ch, &count) == 2) {
        for (int i = 0; i < count; ++i) {
            fputc(ch, decompressed);
        }
    }

    fclose(compressed);
    fclose(decompressed);
    printf("File decompressed to %s\n", decompressedFilename);
    return 0;
}
