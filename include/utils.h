
// include/utils.h

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>  // For FILE type
#include <stdlib.h> // For size_t type

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

/**
 * @brief Safely concatenates two strings.
 *
 * Concatenates the source string to the destination string. Ensures that the
 * destination string does not get overrun by limiting the number of characters
 * copied from the source string.
 *
 * @param dest The destination string.
 * @param src The source string to append to the destination.
 * @param dest_size The total size of the destination buffer.
 * @return A pointer to the resulting string (destination).
 */
char* safe_strcat(char* dest, const char* src, size_t dest_size);

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
 * Determines whether a file exists at the given path.
 *
 * @param filename The path of the file to check.
 * @return Non-zero if the file exists, zero otherwise.
 */
int file_exists(const char* filename);

/**
 * @brief Checks if a given path is a directory.
 *
 * Determines whether the given path corresponds to a directory.
 *
 * @param filename The path to be checked.
 * @return Non-zero if the path is a directory, zero if it is not,
 *         and -1 if the path does not exist or cannot be accessed.
 */
int is_directory(const char* filename);

/**
 * @brief Prints an error message based on the global variable `errno`.
 *
 * If an error occurs during file operations, this function prints an appropriate
 * error message based on the value of `errno`.
 *
 * @param message A custom message to precede the error description.
 */
void print_error(const char* message);

#endif // UTILS_H
