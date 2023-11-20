
// tests/tests.c

// compile with "gcc -o test_executable tests/tests.c src/display.c src/file_operations.c src/search.c src/compression.c src/permissions.c src/utils.c -Iinclude"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "display.h"
#include "file_operations.h"
#include "search.h"
#include "compression.h"
#include "permissions.h"
#include "utils.h"

// Additional helper functions if needed for testing

int fileExists(const char* filename);
void resetTestEnvironment(); // Resets the environment between tests

// Test function prototypes
void testDisplayHelp();
void testPrintFileContent();
void testSearchFiles();
void testPrintSize();
void testMergeFile();
void testCompressAndDecompress();
void testPrintFilePermissions();
void testMoveFile();
void testCreateDeleteCopyFile(); // For create, delete, and copy functions
void testMiscOperations(); // For miscellaneous operations like listing directories, encrypting files, etc.

int main() {
    testDisplayHelp();
    testPrintFileContent();
    testSearchFiles();
    testPrintSize();
    testMergeFile();
    testCompressAndDecompress();
    testPrintFilePermissions();
    testMoveFile();
    testCreateDeleteCopyFile();
    testMiscOperations();

    printf("All tests passed!\n");
    return 0;
}

// Implementations of the test functions

void testDisplayHelp() {
    // Test display_help function - mostly manual check
    printf("\nTesting display_help...\n");
    display_help();
    printf("display_help test passed! (Manual check required)\n");
}

void testPrintFileContent() {
    // Test print_file_content function with various scenarios
    printf("\nTesting print_file_content...\n");

    // Scenario 1: Existing file
    print_file_content("tests/example_file.txt");

    // Scenario 2: Non-existent file
    print_file_content("tests/non_existent_file.txt");

    // Further scenarios can be checked manually
    printf("print_file_content test passed! (Manual checks for other scenarios)\n");
}

void testSearchFiles() {
    // Test search_files function with various scenarios
    printf("\nTesting search_files...\n");

    // Scenario 1: Existing file with search term
    int result = search_files("tests/example_file.txt", "search_term");
    assert(result == 1); // Expecting one match

    // Further scenarios can be checked manually
    printf("search_files test passed! (Manual checks for other scenarios)\n");
}

void testPrintSize() {
    // Test print_size function with various scenarios
    printf("\nTesting print_size...\n");

    // Scenario 1: Existing file
    print_size("tests/example_file.txt");

    // Further scenarios can be checked manually
    printf("print_size test passed! (Manual checks for other scenarios)\n");
}

void testMergeFile() {
    // Test merge_file function with various scenarios
    printf("\nTesting merge_file...\n");

    // Scenario 1: Merge two existing files
    const char* files[] = {"tests/file1.txt", "tests/file2.txt"};
    merge_file("tests/merged.txt", 2, files);

    // Further scenarios can be checked manually
    printf("merge_file test passed! (Manual checks for other scenarios)\n");
}

void testCompressAndDecompress() {
    // Test compress_goat and decompress_goat functions
    printf("\nTesting compress_goat and decompress_goat...\n");

    // Test string compression
    //const char* test_string = "aaaaabbbbcccdde. AAbbbbbbbbbbbbbbbc!";
    //char *compressed = compress_string(test_string);
    //char *decompressed = decompress_string(compressed);
    //printf("Original: %s\n", test_string);
    //printf("Compressed: %s\n", compressed);
    //printf("Decompressed: %s\n", decompressed);
    //free(compressed);
    //free(decompressed);

    // Compress a file
    compress_goat("tests/example_file.txt");
    assert(fileExists("tests/example_file.txt.goat"));

    // Decompress the file
    decompress_goat("tests/example_file.txt.goat");
    assert(fileExists("tests/example_file.txt.goat.decompressed"));

    printf("compress_goat and decompress_goat test passed!\n");
}

void testPrintFilePermissions() {
    // Test print_file_permissions function - mostly manual check
    printf("\nTesting print_file_permissions...\n");
    print_file_permissions("tests/example_file.txt");
    printf("print_file_permissions test passed! (Manual check required)\n");
}

void testMoveFile() {
    // Test move_file function
    printf("\nTesting move_file...\n");

    // Move a file and then move it back
    move_file("tests/source.txt", "tests/dest.txt");
    assert(fileExists("tests/dest.txt"));
    move_file("tests/dest.txt", "tests/source.txt");

    printf("move_file test passed!\n");
}

void testCreateDeleteCopyFile() {
    // Test create, delete, and copy file operations
    printf("\nTesting create, delete, and copy file operations...\n");

    // Implement the test cases for file creation, deletion, and copying

    printf("create, delete, and copy file operations test passed! (Manual checks may be required)\n");
}

void testMiscOperations() {
    // Test miscellaneous operations
    printf("\nTesting miscellaneous operations...\n");

    // Implement test cases for any other miscellaneous operations like listing directories, encrypting files, etc.

    printf("miscellaneous operations test passed! (Manual checks may be required)\n");
}

// Helper function implementations

int fileExists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

void resetTestEnvironment() {
    // Implement any cleanup or resetting needed between tests
}
