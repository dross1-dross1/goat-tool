
// include/file_operations.h

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

// Function prototype for print_file_content
void print_file_content(const char* filename);
void print_size(const char* filename);
int merge_file(const char* output_file, int num_files, const char** input_files);
int move_file(const char* source, const char* destination);

#endif // FILE_OPERATIONS_H
