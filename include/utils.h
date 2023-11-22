
// include/utils.h

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>  // For FILE type
#include <stdlib.h> // For size_t type
#include <sys/stat.h> // For struct stat

/**
 * @brief Reads a line from the given file.
 *
 * Reads a line from the specified file into the provided buffer. Reading stops
 * after an End-Of-File or when the buffer is full.
 *
 * @param file A pointer to the FILE from which the line is to be read.
 * @param buffer The buffer where the read line will be stored.
 * @param buffer_size The size of the buffer.
 * @return A pointer to the buffer containing the line. Returns NULL if no line is read.
 */
char* read_line(FILE* file, char* buffer, size_t buffer_size);

/**
 * @brief Checks if a file exists.
 *
 * Checks the existence of a file with the specified filename.
 *
 * @param filename The path of the file to check.
 * @return 1 if the file exists, 0 otherwise.
 */
int file_exists(const char* filename);

/**
 * @brief Checks if a given filename is a directory.
 *
 * Determines if the specified filename is a directory.
 *
 * @param filename The path of the file to check.
 * @return 1 if it's a directory, 0 if not, and -1 if an error occurs.
 */
int is_directory(const char* filename);

/**
 * @brief Prints an error message based on the global errno.
 *
 * This function prints an error message corresponding to the current value
 * of the global errno. It covers a range of common file-related errors.
 */
void print_error();

/**
 * @brief Opens a file with the specified mode.
 *
 * Attempts to open a file with the given filename and mode (e.g., "r" for read,
 * "w" for write). If the file cannot be opened, an error message is printed.
 *
 * @param filename The path of the file to be opened.
 * @param mode The mode in which the file is to be opened.
 * @return A pointer to the opened FILE. Returns NULL if the file cannot be opened.
 */
FILE* open_file(const char* filename, const char* mode);

#endif // UTILS_H
