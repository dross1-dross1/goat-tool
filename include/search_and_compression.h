// search_and_compression.h
#ifndef SEARCH_AND_COMPRESSION_H
#define SEARCH_AND_COMPRESSION_H

// Function declarations
void list_directory(const char* directory);
int search_files(const char* directory, const char* query);
int encrypt_file(const char* filename, const char* password);
void print_file_content(const char* filename);
int compress_goat(const char* filename);
int decompress_goat(const char* filename);
void print_file_permissions(const char* filename);

#endif
