
// include/permissions.h

#ifndef PERMISSIONS_H
#define PERMISSIONS_H

/**
 * @brief Prints the file permissions of the specified file as an octal number.
 *
 * This function examines the permissions of a given file and prints them in octal format.
 * It checks for read, write, and execute permissions for the user, group, and others.
 * If the file does not exist or cannot be accessed due to permissions, an error message
 * is printed. If no filename is provided, an error is also printed.
 *
 * The function returns 0 on success or -1 in case of an error, along with an appropriate
 * error message.
 *
 * Example output: "Permissions for 'example.txt': 0644"
 *
 * @param filename The path of the file whose permissions are to be printed.
 *                 If NULL or empty, an error message is printed.
 * @return 0 on success, -1 on error.
 */
int print_file_permissions(const char* filename);

#endif // PERMISSIONS_H
