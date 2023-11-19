// search_and_compression.c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fnmatch.h>
#include <string.h>
#include <zlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "search_and_compression.h"

// Function definitions
void list_directory(const char* directory) {
    // Implementation for listing a directory
    DIR *dir;
    struct dirent *entry;

    // Open the directory
    dir = opendir(directory);

    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);
}

int search_files(const char* directory, const char* query) {
    DIR *dir;
    struct dirent *entry;
    int match_count = 0;

    // Open the directory
    dir = opendir(directory);

    if (dir == NULL) {
        perror("Error opening directory");
        return -1;  // Return -1 for failure
    }

    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Use fnmatch to check if the entry matches the query
        if (fnmatch(query, entry->d_name, 0) == 0) {
            printf("Match found: %s\n", entry->d_name);
            match_count++;
        }
}

int encrypt_file(const char* filename, const char* password) {
    FILE* file = fopen(filename, "rb");
    FILE* encrypted_file = fopen("encrypted_file.bin", "wb");

    if (file == NULL || encrypted_file == NULL) {
        perror("Error opening files");
        return 1;  // Return non-zero for failure
    }

    // Get the length of the password
    size_t password_length = strlen(password);

    int ch;
    size_t i = 0;

    // Read each character from the file
    while ((ch = fgetc(file)) != EOF) {
        // XOR each character with the corresponding character in the password
        fputc(ch ^ password[i % password_length], encrypted_file);

        // Increment the password index
        i++;
    }

    // Close the files
    fclose(file);
    fclose(encrypted_file);

    printf("File \"%s\" encrypted successfully.\n", filename);

    return 0;  // Return zero for success
}


void print_file_content(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int ch;

    // Read each character from the file and print it to the console
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // Close the file
    fclose(file);
}

int compress_goat(const char* filename) {
    FILE* file = fopen(filename, "rb");
    FILE* compressed_file = fopen("compressed_file.goat", "wb");

    if (file == NULL || compressed_file == NULL) {
        perror("Error opening files");
        return 1;  // Return non-zero for failure
    }

    // Set up zlib compression parameters
    z_stream stream;
    memset(&stream, 0, sizeof(stream));

    if (deflateInit(&stream, Z_BEST_COMPRESSION) != Z_OK) {
        fclose(file);
        fclose(compressed_file);
        fprintf(stderr, "Error initializing compression\n");
        return 1;  // Return non-zero for failure
    }

    // Read and compress the file in chunks
    const int chunk_size = 1024;
    unsigned char in_buffer[chunk_size];
    unsigned char out_buffer[chunk_size];

    do {
        stream.avail_in = fread(in_buffer, 1, chunk_size, file);
        if (ferror(file)) {
            deflateEnd(&stream);
            fclose(file);
            fclose(compressed_file);
            fprintf(stderr, "Error reading from file\n");
            return 1;  // Return non-zero for failure
        }

        stream.next_in = in_buffer;

        do {
            stream.avail_out = chunk_size;
            stream.next_out = out_buffer;

            if (deflate(&stream, Z_FINISH) == Z_STREAM_ERROR) {
                deflateEnd(&stream);
                fclose(file);
                fclose(compressed_file);
                fprintf(stderr, "Error compressing file\n");
                return 1;  // Return non-zero for failure
            }

            size_t compressed_size = chunk_size - stream.avail_out;
            fwrite(out_buffer, 1, compressed_size, compressed_file);

        } while (stream.avail_out == 0);

    } while (!feof(file));

    // Clean up zlib compression
    deflateEnd(&stream);

    // Close the files
    fclose(file);
    fclose(compressed_file);

    printf("File \"%s\" compressed to \"%s\" successfully.\n", filename, "compressed_file.goat");

    return 0;  // Return zero for success
}


int decompress_goat(const char* filename) {
        FILE* compressed_file = fopen(filename, "rb");
    FILE* decompressed_file = fopen("decompressed_file.txt", "wb");

    if (compressed_file == NULL || decompressed_file == NULL) {
        perror("Error opening files");
        return 1;  // Return non-zero for failure
    }

    // Set up zlib decompression parameters
    z_stream stream;
    memset(&stream, 0, sizeof(stream));

    if (inflateInit(&stream) != Z_OK) {
        fclose(compressed_file);
        fclose(decompressed_file);
        fprintf(stderr, "Error initializing decompression\n");
        return 1;  // Return non-zero for failure
    }

    // Read and decompress the file in chunks
    const int chunk_size = 1024;
    unsigned char in_buffer[chunk_size];
    unsigned char out_buffer[chunk_size];

    do {
        stream.avail_in = fread(in_buffer, 1, chunk_size, compressed_file);
        if (ferror(compressed_file)) {
            inflateEnd(&stream);
            fclose(compressed_file);
            fclose(decompressed_file);
            fprintf(stderr, "Error reading from compressed file\n");
            return 1;  // Return non-zero for failure
        }

        stream.next_in = in_buffer;

        do {
            stream.avail_out = chunk_size;
            stream.next_out = out_buffer;

            if (inflate(&stream, Z_NO_FLUSH) == Z_STREAM_ERROR) {
                inflateEnd(&stream);
                fclose(compressed_file);
                fclose(decompressed_file);
                fprintf(stderr, "Error decompressing file\n");
                return 1;  // Return non-zero for failure
            }

            size_t decompressed_size = chunk_size - stream.avail_out;
            fwrite(out_buffer, 1, decompressed_size, decompressed_file);

        } while (stream.avail_out == 0);

    } while (!feof(compressed_file));

    // Clean up zlib decompression
    inflateEnd(&stream);

    // Close the files
    fclose(compressed_file);
    fclose(decompressed_file);

    printf("File \"%s\" decompressed to \"%s\" successfully.\n", filename, "decompressed_file.txt");

    return 0;  // Return zero for success
}

void print_file_permissions(const char* filename) {
    struct stat file_stat;

    if (stat(filename, &file_stat) == -1) {
        perror("Error getting file information");
        return;
    }

    // Extract and print file permissions as an integer
    mode_t permissions = file_stat.st_mode & 0777;  // Extract the permission bits
    printf("Permissions: %o\n", permissions);
}
