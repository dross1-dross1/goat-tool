#!/bin/bash

TEST_DIR="test_files"
BINARY="./bin/goattool"
ECHO_PREFIX="[GT-Test]"

# Exsisting files
EXAMPLE_FILE="${TEST_DIR}/example_file.txt"
FILE1="${TEST_DIR}/file1.txt"
FILE2="${TEST_DIR}/file2.txt"
LOCKED_FILE="${TEST_DIR}/locked_file.txt"
SOURCE_FILE="${TEST_DIR}/source_file.txt"
EMPTY_FILE="${TEST_DIR}/empty_file.txt"
SPECIAL_FILE="${TEST_DIR}/special@file#.txt"
GOAT_LOCKED_FILE="${TEST_DIR}/locked_file.txt.goat"
DEGOAT_LOCKED_FILE="${TEST_DIR}/locked_file.txt.goat.decompressed"

# Non-existant files
NON_EXISTENT_FILE="${TEST_DIR}/non_existent_file.txt"
GOAT_NON_EXISTENT_FILE="${TEST_DIR}/non_existent_file.txt.goat"

# Generated files
MERGED_FILE="${TEST_DIR}/merged.txt"
GOAT_EXAMPLE_FILE="${TEST_DIR}/example_file.txt.goat"
GOAT_EMPTY_FILE="${TEST_DIR}/empty_file.txt.goat"
GOAT_SPECIAL_FILE="${TEST_DIR}/special@file#.txt.goat"
DEGOAT_EXAMPLE_FILE="${TEST_DIR}/example_file.txt.goat.decompressed"
DEGOAT_EMPTY_FILE="${TEST_DIR}/empty_file.txt.goat.decompressed"
DEGOAT_SPECIAL_FILE="${TEST_DIR}/special@file#.txt.goat.decompressed"
DESTINATION_FILE="${TEST_DIR}/destination_file.txt"

# Enable verbose output (1 for on, 0 for off)
VERBOSE_ON=1

# Initialize test counters
total_tests=0
passed_tests=0
failed_tests=0

printMsg() {
    local newline_flag="$1"
    local text="$2"
    if [[ "$newline_flag" -eq 1 ]]; then
        echo -e "\n${ECHO_PREFIX} $text"
    else
        echo -e "${ECHO_PREFIX} $text"
    fi
}

runTest() {
    local command="$1"
    local expected_output="$2"
    local actual_output

    actual_output=$(eval "$command")

    if [[ $VERBOSE_ON == 1 ]]; then
        printMsg 0 "CASE: $command"
        printMsg 0 "EXPECTED:\n$expected_output"
        printMsg 0 "ACTUAL:\n$actual_output"
    fi

    ((total_tests++))
    if [[ "$actual_output" == "$expected_output" ]]; then
        printMsg 0 "RESULT: PASS"
        ((passed_tests++))
    else
        printMsg 0 "RESULT: FAIL"
        ((failed_tests++))
    fi
}

prepareTestEnvironment() {
    printMsg 0 "Preparing test environment"
    chmod 000 "$LOCKED_FILE"
    chmod 000 "$GOAT_LOCKED_FILE"
    chmod 000 "$DEGOAT_LOCKED_FILE"
    chmod 777 "$EMPTY_FILE"
    printMsg 0 "Test environment prepared"
}

resetTestEnvironment() {
    printMsg 1 "Clearing test environment"
    chmod 664 "$LOCKED_FILE"
    chmod 664 "$GOAT_LOCKED_FILE"
    chmod 664 "$DEGOAT_LOCKED_FILE"
    chmod 664 "$EMPTY_FILE"
    [ -f "$MERGED_FILE" ] && rm "$MERGED_FILE"
    [ -f "$GOAT_EXAMPLE_FILE" ] && rm "$GOAT_EXAMPLE_FILE"
    [ -f "$GOAT_EMPTY_FILE" ] && rm "$GOAT_EMPTY_FILE"
    [ -f "$GOAT_SPECIAL_FILE" ] && rm "$GOAT_SPECIAL_FILE"
    [ -f "$DEGOAT_EXAMPLE_FILE" ] && rm "$DEGOAT_EXAMPLE_FILE"
    [ -f "$DEGOAT_EMPTY_FILE" ] && rm "$DEGOAT_EMPTY_FILE"
    [ -f "$DEGOAT_SPECIAL_FILE" ] && rm "$DEGOAT_SPECIAL_FILE"
    [ -f "$DESTINATION_FILE" ] && rm "$DESTINATION_FILE"
    printMsg 0 "Test environment cleared"
}

main() {
    printMsg 0 "START"
    prepareTestEnvironment

    # Operation 1: `-h` (Display the help menu)
    printMsg 1 "[-h] Test case: Print the help menu"
    runTest "$BINARY -h" \
"GoatTool Help and Usage Instructions
------------------------------------
-h : Display this help menu.
-p [FILENAMES...] : Print the contents of one or more files.
-s [SEARCH_TERM] [FILENAME] : Search a file for a string.
-z [FILENAME] : Print the size of a file.
-m [OUTPUT_FILE] [INPUT_FILES...] : Merge multiple files.
-c [FILENAME] : Compress a file into .goat format.
-d [FILENAME] : Decompress a .goat file.
-r [FILENAME] : Print file permissions.
-v [SOURCE] [DESTINATION] : Move or rename a file."

    # Operation 2: `-p [FILENAME]` (Print the contents of a file)
    printMsg 1 "[-p] Test case: Print the contents of a single file"
    runTest "$BINARY -p $EXAMPLE_FILE" \
"--- Content of 'test_files/example_file.txt' ---
This is an example file.
It has multiple lines.
And it is used for testing purposes.
Make sure you have fun testing!
This is a line with search_term.
aaaaaaaaaaaaaaaaaabbbb cccdde"

    printMsg 1 "[-p] Test case: Print the contents of a file that doesn't exist"
    runTest "$BINARY -p $NON_EXISTENT_FILE" \
"Error: Cannot access 'test_files/non_existent_file.txt' because it does not exist."

    printMsg 1 "[-p] Test case: Print the contents of multiple existing files"
    runTest "$BINARY -p $FILE1 $FILE2" \
"--- Content of 'test_files/file1.txt' ---
This is the first file.
It will be merged with another.
--- Content of 'test_files/file2.txt' ---
This is the second file.
Merged content goes below the first file's content."

    printMsg 1 "[-p] Test case: Print the contents of a mix of existing and non-existing files"
    runTest "$BINARY -p $FILE1 $NON_EXISTENT_FILE" \
"--- Content of 'test_files/file1.txt' ---
This is the first file.
It will be merged with another.
Error: Cannot access 'test_files/non_existent_file.txt' because it does not exist."

    printMsg 1 "[-p] Test case: Print the contents with one of the files being a directory"
    runTest "$BINARY -p $EXAMPLE_FILE ${TEST_DIR}" \
"--- Content of 'test_files/example_file.txt' ---
This is an example file.
It has multiple lines.
And it is used for testing purposes.
Make sure you have fun testing!
This is a line with search_term.
aaaaaaaaaaaaaaaaaabbbb cccdde
Error: Cannot access 'test_files' because it is a directory."

    printMsg 1 "[-p] Test case: Print the contents of an empty file"
    runTest "$BINARY -p $EMPTY_FILE" \
"--- Content of 'test_files/empty_file.txt' ---"

    printMsg 1 "[-p] Test case: Print the contents with no files specified"
    runTest "$BINARY -p" \
"Error: Invalid command switch or missing arguments. Use -h for help."

    # Operation 3: `-s [SEARCH_TERM] [FILENAME]` (Search a file for a string)
    printMsg 1 "[-s] Test case: Search for a term in a file (existing term)"
    runTest "$BINARY -s \"search_term\" $EXAMPLE_FILE" \
"Line 5: This is a line with search_term."

    printMsg 1 "[-s] Test case: Search for a term that doesn't exist in the file"
    runTest "$BINARY -s \"missing_term\" $EXAMPLE_FILE" \
"No matches found for 'missing_term'."

    printMsg 1 "[-s] Test case: No search term or filename provided"
    runTest "$BINARY -s" \
"Error: Invalid command switch or missing arguments. Use -h for help."

    printMsg 1 "[-s] Test case: No filename provided"
    runTest "$BINARY -s \"search_term\"" \
"Error: Invalid command switch or missing arguments. Use -h for help."

    printMsg 1 "[-s] Test case: File does not exist"
    runTest "$BINARY -s \"search_term\" $NON_EXISTENT_FILE" \
"Error: Cannot access 'test_files/non_existent_file.txt' because it does not exist."

    printMsg 1 "[-s] Test case: Search term is an empty string"
    runTest "$BINARY -s \"\" $EXAMPLE_FILE" \
"Line 1: This is an example file.
Line 2: It has multiple lines.
Line 3: And it is used for testing purposes.
Line 4: Make sure you have fun testing!
Line 5: This is a line with search_term.
Line 6: aaaaaaaaaaaaaaaaaabbbb cccdde"

    printMsg 1 "[-s] Test case: Search in an empty file"
    runTest "$BINARY -s \"search_term\" $EMPTY_FILE" \
"No matches found for 'search_term'."

    # Operation 4: `-z [FILENAME]` (Print the size of a file)
    printMsg 1 "[-z] Test case: Print the size of an existing file"
    runTest "$BINARY -z $EXAMPLE_FILE" \
"Size: 180 bytes."

    printMsg 1 "[-z] Test case: No filename provided"
    runTest "$BINARY -z" \
"Error: Invalid command switch or missing arguments. Use -h for help."

    printMsg 1 "[-z] Test case: File does not exist"
    runTest "$BINARY -z $NON_EXISTENT_FILE" \
"Error: Cannot access 'test_files/non_existent_file.txt' because it does not exist."

    printMsg 1 "[-z] Test case: Specified path is a directory"
    runTest "$BINARY -z $TEST_DIR" \
"Error: Cannot access 'test_files' because it is a directory."

    printMsg 1 "[-z] Test case: File with access denied (locked file)"
    runTest "$BINARY -z $LOCKED_FILE" \
"Error: Cannot access 'test_files/locked_file.txt' due to insufficient permissions."

    printMsg 1 "[-z] Test case: Print the size of an empty file"
    runTest "$BINARY -z $EMPTY_FILE" \
"Size: 0 bytes."

    printMsg 1 "[-z] Test case: File with special characters in the name"
    runTest "$BINARY -z $SPECIAL_FILE" \
"Size: 22 bytes."

    # Operation 5: `-m [OUTPUT_FILE] [INPUT_FILES...]` (Merge multiple files)
    printMsg 1 "[-m] Test case: Merge two files together"
    runTest "$BINARY -m $MERGED_FILE $FILE1 $FILE2 && $BINARY -p $MERGED_FILE" \
"Files merged successfully into 'test_files/merged.txt'.
--- Content of 'test_files/merged.txt' ---
This is the first file.
It will be merged with another.
This is the second file.
Merged content goes below the first file's content."

    printMsg 1 "[-m] Test case: Merge with a non-existent file"
    runTest "$BINARY -m $MERGED_FILE $NON_EXISTENT_FILE $FILE2" \
"Error: Cannot access 'test_files/non_existent_file.txt' because it does not exist."

    printMsg 1 "[-m] Test case: No output or input files provided"
    runTest "$BINARY -m" \
"Error: Invalid command switch or missing arguments. Use -h for help."

    printMsg 1 "[-m] Test case: Only output file provided, no input files"
    runTest "$BINARY -m $MERGED_FILE" \
"Error: Invalid command switch or missing arguments. Use -h for help."

    printMsg 1 "[-m] Test case: Merge with a file with access denied"
    runTest "$BINARY -m $MERGED_FILE $FILE1 $LOCKED_FILE" \
"Error: Cannot access 'test_files/locked_file.txt' due to insufficient permissions."

    printMsg 1 "[-m] Test case: Merge with a directory instead of a file"
    runTest "$BINARY -m $MERGED_FILE $TEST_DIR $FILE2" \
"Error: Cannot access 'test_files' because it is a directory."

    printMsg 1 "[-m] Test case: Merge with an empty file"
    runTest "$BINARY -m $MERGED_FILE $EMPTY_FILE $FILE2 && $BINARY -p $MERGED_FILE" \
"Files merged successfully into 'test_files/merged.txt'.
--- Content of 'test_files/merged.txt' ---
This is the second file.
Merged content goes below the first file's content."

    # Operation 6: `-c [FILENAME]` (Compress a file into .goat format)
    printMsg 1 "[-c] Test case: Compress an existing file"
    runTest "$BINARY -c $EXAMPLE_FILE && $BINARY -p $GOAT_EXAMPLE_FILE" \
"File processed to test_files/example_file.txt.goat.
--- Content of 'test_files/example_file.txt.goat' ---
T1h1i1s1 i1s1 a1n1 e1x1a1m1p1l1e1 f1i1l1e1.
I1t1 h1a1s1 m1u1l1t1i1p1l1e1 l1i1n1e1s1.
A1n1d1 i1t1 i1s1 u1s1e1d1 f1o1r1 t1e1s1t1i1n1g1 p1u1r1p1o1s1e1s1.
M1a1k1e1 s1u1r1e1 y1o1u1 h1a1v1e1 f1u1n1 t1e1s1t1i1n1g1!
T1h1i1s1 i1s1 a1 l1i1n1e1 w1i1t1h1 s1e1a1r1c1h1_t1e1r1m1.
a18b4 c3d2e1"

    printMsg 1 "[-c] Test case: No filename provided"
    runTest "$BINARY -c" \
"Error: Invalid command switch or missing arguments. Use -h for help."

    printMsg 1 "[-c] Test case: File does not exist"
    runTest "$BINARY -c $NON_EXISTENT_FILE" \
"Error: Cannot access 'test_files/non_existent_file.txt' because it does not exist."

    printMsg 1 "[-c] Test case: Specified path is a directory"
    runTest "$BINARY -c $TEST_DIR" \
"Error: Cannot access 'test_files' because it is a directory."

    printMsg 1 "[-c] Test case: File with access denied (locked file)"
    runTest "$BINARY -c $LOCKED_FILE" \
"Error: Cannot access 'test_files/locked_file.txt' due to insufficient permissions."

    printMsg 1 "[-c] Test case: Compress an empty file"
    runTest "$BINARY -c $EMPTY_FILE && $BINARY -p $GOAT_EMPTY_FILE" \
"File processed to test_files/empty_file.txt.goat.
--- Content of 'test_files/empty_file.txt.goat' ---"

    printMsg 1 "[-c] Test case: Compress a file with special characters in the name"
    runTest "$BINARY -c $SPECIAL_FILE && $BINARY -p $GOAT_SPECIAL_FILE" \
"File processed to test_files/special@file#.txt.goat.
--- Content of 'test_files/special@file#.txt.goat' ---
#!m1 @ \$p1[-c1!@| /=!|[-"

    # Operation 7: `-d [FILENAME]` (Decompress a .goat file)
    printMsg 1 "[-d] Test case: Decompress an existing .goat file"
    runTest "$BINARY -d $GOAT_EXAMPLE_FILE && $BINARY -p $DEGOAT_EXAMPLE_FILE" \
"File processed to test_files/example_file.txt.goat.decompressed.
--- Content of 'test_files/example_file.txt.goat.decompressed' ---
This is an example file.
It has multiple lines.
And it is used for testing purposes.
Make sure you have fun testing!
This is a line with search_term.
aaaaaaaaaaaaaaaaaabbbb cccdde"

    printMsg 1 "[-d] Test case: No filename provided"
    runTest "$BINARY -d" \
"Error: Invalid command switch or missing arguments. Use -h for help."

    printMsg 1 "[-d] Test case: .goat file does not exist"
    runTest "$BINARY -d $GOAT_NON_EXISTENT_FILE" \
"Error: Cannot access 'test_files/non_existent_file.txt.goat' because it does not exist."

    printMsg 1 "[-d] Test case: Specified path is a directory"
    runTest "$BINARY -d ${TEST_DIR}" \
"Error: Cannot access 'test_files' because it is a directory."

    printMsg 1 "[-d] Test case: .goat file with access denied"
    runTest "$BINARY -d $GOAT_LOCKED_FILE" \
"Error: Cannot access 'test_files/locked_file.txt.goat' due to insufficient permissions."

    printMsg 1 "[-d] Test case: Decompress an empty .goat file"
    runTest "$BINARY -d $GOAT_EMPTY_FILE && $BINARY -p $DEGOAT_EMPTY_FILE" \
"File processed to test_files/empty_file.txt.goat.decompressed.
--- Content of 'test_files/empty_file.txt.goat.decompressed' ---"

    printMsg 1 "[-d] Test case: .goat file with special characters in the name"
    runTest "$BINARY -d $GOAT_SPECIAL_FILE && $BINARY -p $DEGOAT_SPECIAL_FILE" \
"File processed to test_files/special@file#.txt.goat.decompressed.
--- Content of 'test_files/special@file#.txt.goat.decompressed' ---
#!m @ \$p[-c!@| /=!|[-"

     # Operation 8: `-r [FILENAME]` (Print file permissions)
    printMsg 1 "[-r] Test case: Existing file with standard permissions"
    runTest "$BINARY -r $EXAMPLE_FILE" \
"Permissions for 'test_files/example_file.txt': 664"

    printMsg 1 "[-r] Test case: No filename provided"
    runTest "$BINARY -r" \
"Error: Invalid command switch or missing arguments. Use -h for help."

    printMsg 1 "[-r] Test case: Non-existent file"
    runTest "$BINARY -r $NON_EXISTENT_FILE" \
"Error: File 'test_files/non_existent_file.txt' does not exist."

    printMsg 1 "[-r] Test case: Locked file"
    runTest "$BINARY -r $LOCKED_FILE" \
"Permissions for 'test_files/locked_file.txt': 000"

    printMsg 1 "[-r] Test case: Directory"
    runTest "$BINARY -r $TEST_DIR" \
"Permissions for 'test_files': 775"

    printMsg 1 "[-r] Test case: File with special characters in name"
    runTest "$BINARY -r $SPECIAL_FILE" \
"Permissions for 'test_files/special@file#.txt': 664"

    printMsg 1 "[-r] Test case: Executable file"
    runTest "$BINARY -r $EMPTY_FILE" \
"Permissions for 'test_files/empty_file.txt': 777"

    # Operation 9: `-v [SOURCE] [DESTINATION]` (Move or rename a file)
    printMsg 1 "[-v] Test case: Locked source file"
    runTest "$BINARY -v $LOCKED_FILE $DESTINATION_FILE" \
"Error: Cannot access 'test_files/locked_file.txt' due to insufficient permissions."

    printMsg 1 "[-v] Test case: Successful file move/rename"
    runTest "$BINARY -v $MERGED_FILE $DESTINATION_FILE && $BINARY -p $DESTINATION_FILE" \
"File moved/renamed successfully.
--- Content of 'test_files/destination_file.txt' ---
This is the second file.
Merged content goes below the first file's content."

    printMsg 1 "[-v] Test case: No source or destination provided"
    runTest "$BINARY -v" \
"Error: Invalid command switch or missing arguments. Use -h for help."

    printMsg 1 "[-v] Test case: Non-existent source file"
    runTest "$BINARY -v $NON_EXISTENT_FILE $DESTINATION_FILE" \
"Error: Cannot access 'test_files/non_existent_file.txt' because it does not exist."

    printMsg 1 "[-v] Test case: No destination provided"
    runTest "$BINARY -v $MERGED_FILE" \
"Error: Invalid command switch or missing arguments. Use -h for help."

    printMsg 1 "[-v] Test case: Source is a directory"
    runTest "$BINARY -v $TEST_DIR $DESTINATION_FILE" \
"Error: Cannot access 'test_files' because it is a directory."

    printMsg 1 "[-v] Test case: Destination already exists"
    runTest "$BINARY -v $GOAT_EXAMPLE_FILE $DESTINATION_FILE && $BINARY -p $DESTINATION_FILE" \
"File moved/renamed successfully.
--- Content of 'test_files/destination_file.txt' ---
T1h1i1s1 i1s1 a1n1 e1x1a1m1p1l1e1 f1i1l1e1.
I1t1 h1a1s1 m1u1l1t1i1p1l1e1 l1i1n1e1s1.
A1n1d1 i1t1 i1s1 u1s1e1d1 f1o1r1 t1e1s1t1i1n1g1 p1u1r1p1o1s1e1s1.
M1a1k1e1 s1u1r1e1 y1o1u1 h1a1v1e1 f1u1n1 t1e1s1t1i1n1g1!
T1h1i1s1 i1s1 a1 l1i1n1e1 w1i1t1h1 s1e1a1r1c1h1_t1e1r1m1.
a18b4 c3d2e1"

    # Default Case (No switch provided or invalid switch provided)
    printMsg 1 "[] Test case: No arguments provided"
    runTest "$BINARY" \
"Error: Insufficient argument count. Use -h for help."

    printMsg 1 "[-e] Test case: Invalid switch provided"
    runTest "$BINARY" \
"Error: Insufficient argument count. Use -h for help."

    printMsg 1 "[] Test case: No switch provided but arguments exist"
    runTest "$BINARY $FILE1 $FILE2" \
"Error: Invalid command switch or missing arguments. Use -h for help."

    resetTestEnvironment
    printMsg 0 "END"
    printMsg 1 "TEST SUMMARY"
    printMsg 0 "$total_tests tests total"
    printMsg 0 "$passed_tests tests passed"
    printMsg 0 "$failed_tests tests failed"
}

main

