
// include/compression.h

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stddef.h> // For size_t

/**
 * @brief Compresses a string using a custom compression algorithm.
 *
 * This function compresses the input string `str` by counting consecutive occurrences
 * of each character. For example, "aaabb" becomes "a3b2". Non-alphabetic characters
 * are copied as-is.
 *
 * @param str The string to be compressed.
 * @return A newly allocated string containing the compressed data, or NULL if
 *         an error occurs (e.g., memory allocation fails).
 */
char* compress_string(const char* str);

/**
 * @brief Decompresses a string that was compressed using the custom compression algorithm.
 *
 * This function reverses the compression performed by `compress_string`. For example,
 * "a3b2" is decompressed to "aaabb". Non-alphabetic characters are copied as-is.
 *
 * @param str The string to be decompressed.
 * @return A newly allocated string containing the decompressed data, or NULL if
 *         an error occurs (e.g., memory allocation fails).
 */
char* decompress_string(const char* str);

/**
 * @brief Compresses or decompresses a line of text.
 *
 * This function is a generic line processing function used for parallel
 * processing of file lines. It applies either compression or decompression
 * based on the function pointer provided.
 *
 * @param arg A pointer to LineData containing the line to be processed.
 * @return NULL
 */
void* process_line(void* arg);

/**
 * @brief Processes a file using a specified line processing function.
 *
 * This function reads a file line by line and uses multiple threads to
 * compress or decompress each line. The processed lines are then written
 * to an output file.
 *
 * @param filename The path of the file to process.
 * @param output_filename The path of the file to write processed lines.
 * @param process_line The function to use for line processing.
 * @return 0 on success, -1 on failure.
 */
int process_file(const char* filename, const char* output_filename, void* (*process_line)(void*));

/**
 * @brief Compresses the contents of a file using the custom compression algorithm.
 *
 * This function reads the contents of a file specified by `filename`, compresses each line
 * using `compress_string`, and writes the compressed data to a new file with the same name
 * but with a ".goat" extension.
 *
 * @param filename The path of the file to compress.
 * @return 0 on success, -1 on failure (e.g., file not found, permission denied).
 */
int compress_goat(const char* filename);

/**
 * @brief Decompresses a .goat file to its original content.
 *
 * This function reads a .goat file specified by `filename`, decompresses each line
 * using `decompress_string`, and writes the decompressed data to a new file with the
 * same name but with ".decompressed" appended.
 *
 * @param filename The path of the .goat file to decompress.
 * @return 0 on success, -1 on failure (e.g., file not found, permission denied).
 */
int decompress_goat(const char* filename);

#endif // COMPRESSION_H
