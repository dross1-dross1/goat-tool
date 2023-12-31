
// include/file_operations.h

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdio.h>

/**
 * @brief Prints the content of specified files to the console.
 *
 * This function reads the content from each file specified in the `filenames`
 * array and prints it to the console. It checks for file existence and whether
 * each file is a directory. The function iterates through the number of files
 * specified by `num_files`.
 *
 * @param num_files The number of files to print.
 * @param filenames The array of paths to the files.
 * @return 0 on success, -1 on failure.
 */
int print_file_content(int num_files, const char** filenames);

/**
 * @brief Prints the size of a specified file in bytes.
 *
 * This function calculates the size of the file specified by `filename`
 * and prints its size in bytes to the console. It checks if the file
 * is a directory and handles file existence.
 *
 * @param filename The path to the file.
 * @return 0 on success, -1 on failure.
 */
int print_size(const char* filename);

/**
 * @brief Merges multiple files into one output file.
 *
 * This function takes an array of input file paths and merges their
 * content into a single output file. The merging is done in the
 * order of the files in the array.
 *
 * @param output_file The path to the output file.
 * @param num_files The number of input files.
 * @param input_files The array of paths to the input files.
 * @return 0 on success, -1 on failure.
 */
int merge_file(const char* output_file, int num_files, const char** input_files);

/**
 * @brief Moves or renames a file.
 *
 * This function moves a file from a source path to a destination path.
 * It can also be used to rename the file.
 *
 * @param source The path to the source file.
 * @param destination The path to the destination file or new file name.
 * @return 0 on success, -1 on failure.
 */
int move_file(const char* source, const char* destination);

#endif // FILE_OPERATIONS_H
