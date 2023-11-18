// file_operations.h
#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

// Function declarations
int create_file(const char* filename);
int delete_file(const char* filename);
int copy_file(const char* source, const char* destination);
int move_file(const char* source, const char* destination);

#endif
