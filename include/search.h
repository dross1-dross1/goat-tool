
// include/search.h

#ifndef SEARCH_H
#define SEARCH_H

/**
 * @brief Searches for a specific term within a file and prints the lines containing that term.
 *
 * This function opens the file specified by `filename` and searches each line for the
 * `search_term`. If a line contains the `search_term`, it prints the line along with its
 * line number. The function counts and returns the number of lines where the `search_term`
 * is found.
 *
 * If the file does not exist, cannot be opened, or if either the `filename` or `search_term`
 * is missing, appropriate error messages are displayed.
 *
 * @param search_term The term to search for within the file.
 * @param filename The path to the file in which to search.
 * @return The number of lines where the `search_term` is found, or -1 in case of an error.
 */
int search_files(const char* search_term, const char* filename);

#endif // SEARCH_H
