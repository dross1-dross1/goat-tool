# Goat Tool Documentation

**Authors:**
- Jaret Smith
- Deautaun Ross
- Johan Olvera
- ChatGPT

---

## Table of Contents
0. [Project File Structure](#project-file-structure)
1. [Introduction](#introduction)
2. [Command Switches](#command-switches)
3. [Usage Examples](#usage-examples)
4. [Functions](#functions)
5. [Test Cases](#test-cases)
6. [Privacy Disclosure](#privacy-disclosure)

---

## Project File Structure

```
GoatTool/
│
├── README.md                     # Overview of the tool, how to install and basic usage
│
├── .gitignore                    # Git ignore file to exclude unnecessary files
│
├── Makefile                      # Used for compilation and possibly testing
│
├── src/                          # Contains the source code files
│   ├── main.c                    # Entry point for the GoatTool
│   ├── display.c                 # Contains functions related to displaying data (like `display_help`)
│   ├── file_operations.c         # Contains file related operations (create, delete, copy, move etc.)
│   ├── search.c                  # Contains functions related to file searching (`search_files`)
│   ├── compression.c             # Handles .goat compression & decompression (`compress_goat`, `decompress_goat`)
│   ├── permissions.c             # Related to file permissions (`print_file_permissions`)
│   └── utils.c                   # Miscellaneous utility functions (could be error handling, string manipulations, etc.)
│
├── include/                      # Contains header files corresponding to source files
│   ├── display.h                 
│   ├── file_operations.h
│   ├── search.h
│   ├── compression.h
│   ├── permissions.h
│   └── utils.h
│
├── doc/                          # Documentation directory
│   ├── DESIGN.md                 # Design document as per the project requirement
│   └── USAGE.md                  # Extended usage guide based on the provided documentation
│
├── tests/                        # Unit tests (if any are written)
│   ├── test_file_operations.c   
│   ├── test_search.c
│   └── ...
│
└── assets/                       # Any additional assets like images for README or design diagrams
    └── logo.png                  # An example logo for GoatTool (if you have one)
```

---

## Introduction
Goat Tool is a command-line utility for Unix environments, designed to aid in various file and directory operations. To utilize the tool, navigate to a Unix terminal and enter the `./goattool` command followed by the desired switches.

---

## Command Switches

- `-h`: Display the help menu.
  - Usage: `./goattool -h`
 
- `-p [FILENAME]`: Print the contents of a file.
  - Usage: `./goattool -p example.txt`
 
- `-s [FILENAME]`: Search a file for a string and display lines containing that string.
  - Usage: `./goattool -s "search_term" example.txt`
 
- `-z [FILENAME]`: Print the size of a file.
  - Usage: `./goattool -z example.txt`

- `-m [OUTPUT_FILE] [INPUT_FILES...]`: Merge multiple files.
  - Usage: `./goattool -m merged.txt file1.txt file2.txt`
 
- `-c [FILENAME]`: Compress a file into .goat format.
  - Usage: `./goattool -c example.txt`
 
- `-d [FILENAME]`: Decompress a .goat file.
  - Usage: `./goattool -d example.goat`

- `-r [FILENAME]`: Print file permissions.
  - Usage: `./goattool -r example.txt`
 
- `-v [SOURCE] [DESTINATION]`: Move or rename a file.
  - Usage: `./goattool -v source.txt dest.txt`

---

## Usage Examples

1. **Printing File Content**:
```
> ./goattool -p example.txt
This is an example text file.
```

2. **Searching for a String**:
```
> ./goattool -s "text" example.txt
This is an example text file.
```

3. **Compressing and Decompressing**:
```
> ./goattool -c example.txt
File compressed to example.goat

> ./goattool -d example.goat
File decompressed to example.txt
```

---

## Functions

### `void display_help()`
- **Description:** Displays help and usage instructions for GoatTool.
- **Parameters:** None.
- **Return Value:** None.
- **Side Effects:** Outputs help information to the console.

### `int create_file(const char* filename)`
- **Description:** Creates a new file.
- **Parameters:**
  - `filename`: Name of the file to create.
- **Return Value:** 0 for success, non-zero for failure.
- **Side Effects:** Generates a new file in the file system.

### `int delete_file(const char* filename)`
- **Description:** Deletes a specified file.
- **Parameters:**
  - `filename`: Name of the file to delete.
- **Return Value:** 0 for success, non-zero for failure.
- **Side Effects:** Removes the chosen file from the system.

### `int copy_file(const char* source, const char* destination)`
- **Description:** Copies a file from the source to the destination.
- **Parameters:**
  - `source`: Path to the source file.
  - `destination`: Path to the destination file.
- **Return Value:** 0 for success, non-zero for failure.
- **Side Effects:** Duplicates the source file at the destination path.

### `int move_file(const char* source, const char* destination)`
- **Description:** Moves or renames a file.
- **Parameters:**
  - `source`: Path to the source file.
  - `destination`: Path to the destination or new name.
- **Return Value:** 0 for success, non-zero for failure.
- **Side Effects:** Transfers or renames the source file.

### `void list_directory(const char* directory)`
- **Description:** Lists a directory's contents.
- **Parameters:**
  - `directory`: Path to the directory.
- **Return Value:** None.
- **Side Effects:** Outputs directory contents to the console.

### `int search_files(const char* directory, const char* query)`
- **Description:** Searches for files matching a query.
- **Parameters:**
  - `directory`: Directory path for the search.
  - `query`: Search term.
- **Return Value:** Number of matching files.
- **Side Effects:** Outputs details of matching files.

### `int encrypt_file(const char* filename, const char* password)`
- **Description:** Encrypts a file.
- **Parameters:**
  - `filename`: File to encrypt.
  - `password`: Encryption password.
- **Return Value:** 0 for success, non-zero for failure.
- **Side Effects:** Encrypts the specified file.

### `void print_file_content(const char* filename)`
- **Description:** Print the content of the given file.
- **Parameters:**
  - `filename`: Name of the file to print.
- **Return Value:** None.
- **Side Effects:** Outputs file content to the console.

### `int compress_goat(const char* filename)`
- **Description:** Compress a file into .goat format.
- **Parameters:**
  - `filename`: File to compress.
- **Return Value:** 0 for success, non-zero for failure.
- **Side Effects:** Generates a compressed .goat file.

### `int decompress_goat(const char* filename)`
- **Description:** Decompress a .goat file to its original content.
- **Parameters:**
  - `filename`: .goat file to decompress.
- **Return Value:** 0 for success, non-zero for failure.
- **Side Effects:** Generates the original file from the .goat format.

### `void print_file_permissions(const char* filename)`
- **Description:** Print the file permissions as an integer.
- **Parameters:**
  - `filename`: File whose permissions are to be printed.
- **Return Value:** None.
- **Side Effects:** Outputs file permissions to the console.

---

## Test Cases

---

**Operation 1: `-h` (Display the help menu)**
1. Input: `./goattool -h`
   Expected Output: *Help and usage instructions for GoatTool.*

---

**Operation 2: `-p [FILENAME]` (Print the contents of a file)**
1. Input: `./goattool -p example_file.txt`
   Expected Output: "This is an example file".

2. Input: `./goattool -p non_existent_file.txt`
   Expected Output: "Error: File does not exist."

3. Input: `./goattool -p`
   Expected Output: "Error: No filename provided."

4. Input: `./goattool -p directory_name`
   Expected Output: "Error: Cannot print a directory."

5. Input: `./goattool -p locked_file.txt`
   Expected Output: "Error: Permission denied."

---

**Operation 3: `-s [FILENAME]` (Search a file for a string)**
1. Input: `./goattool -s "search_term" example_file.txt`
   Expected Output: "Line 5: This is a line with search_term."

2. Input: `./goattool -s "missing_term" example_file.txt`
   Expected Output: "No matches found."

3. Input: `./goattool -s`
   Expected Output: "Error: No search term or filename provided."

4. Input: `./goattool -s "search_term"`
   Expected Output: "Error: No filename provided."

5. Input: `./goattool -s "search_term" non_existent_file.txt`
   Expected Output: "Error: File does not exist."

---

**Operation 4: `-z [FILENAME]` (Print the size of a file)**
1. Input: `./goattool -z example_file.txt`
   Expected Output: "Size: 500 bytes."

2. Input: `./goattool -z`
   Expected Output: "Error: No filename provided."

3. Input: `./goattool -z non_existent_file.txt`
   Expected Output: "Error: File does not exist."

4. Input: `./goattool -z directory_name`
   Expected Output: "Error: Cannot get the size of a directory."

5. Input: `./goattool -z locked_file.txt`
   Expected Output: "Error: Permission denied."

---

**Operation 5: `-m [OUTPUT_FILE] [INPUT_FILES...]` (Merge multiple files)**
1. Input: `./goattool -m merged.txt file1.txt file2.txt`
   Expected Output: "Files merged successfully."

2. Input: `./goattool -m merged.txt non_existent_file.txt file2.txt`
   Expected Output: "Error: One or more input files do not exist."

3. Input: `./goattool -m`
   Expected Output: "Error: No output or input files provided."

4. Input: `./goattool -m merged.txt`
   Expected Output: "Error: At least two input files are required."

5. Input: `./goattool -m merged.txt file1.txt locked_file.txt`
   Expected Output: "Error: Permission denied for one or more files."

---

**Operation 6: `-c [FILENAME]` (Compress a file into .goat format)**
1. Input: `./goattool -c example_file.txt`
   Expected Output: "File compressed to example_file.goat."

2. Input: `./goattool -c`
   Expected Output: "Error: No filename provided."

3. Input: `./goattool -c non_existent_file.txt`
   Expected Output: "Error: File does not exist."

4. Input: `./goattool -c directory_name`
   Expected Output: "Error: Cannot compress a directory."

5. Input: `./goattool -c locked_file.txt`
   Expected Output: "Error: Permission denied."

---

**Operation 7: `-d [FILENAME]` (Decompress a .goat file)**
1. Input: `./goattool -d example.goat`
   Expected Output: "File decompressed to example.txt."

2. Input: `./goattool -d`
   Expected Output: "Error: No filename provided."

3. Input: `./goattool -d non_existent_file.goat`
   Expected Output: "Error: File does not exist."

4. Input: `./goattool -d directory_name`
   Expected Output: "Error: Cannot decompress a directory."

5. Input: `./goattool -d locked_file.goat`
   Expected Output: "Error: Permission denied."

---

**Operation 8: `-r [FILENAME]` (Print file permissions)**
1. Input: `./goattool -r example_file.txt`
   Expected Output: "Permissions: -rw-r--r--."

2. Input: `./goattool -r`
   Expected Output: "Error: No filename provided."

3. Input: `./goattool -r non_existent_file.txt`
   Expected Output: "Error: File does not exist."

4. Input: `./goattool -r locked_file.txt`
   Expected Output: "Permissions: ---------."

5. Input: `./goattool -r directory_name`
   Expected Output: "Permissions: drwxr-xr-x."

---

**Operation 9: `-v [SOURCE] [DESTINATION]` (Move or rename a file)**
1. Input: `./goattool -v source.txt dest.txt`
   Expected Output: "File moved/renamed successfully."

2. Input: `./goattool -v`
   Expected Output: "Error: No source or destination provided."

3. Input: `./goattool -v non_existent_file.txt dest.txt`
   Expected Output: "Error: Source file does not exist."

4. Input: `./goattool -v source.txt`
   Expected Output: "Error: No destination provided."

5. Input: `./goattool -v locked_file.txt dest.txt`
   Expected Output: "Error: Permission denied."

---

**Default Case (No switch provided)**
1. Input: `./goattool`
   Expected Output: "Error: No command switch provided. Use -h for help."

---

**Sample Files:**
1. **example_file.txt**:
```
This is an example file.
It has multiple lines.
And it is used for testing purposes.
Make sure you have fun testing!
This is a line with search_term.
```

2. **file1.txt**:
```
This is the first file.
It will be merged with another.
```

3. **file2.txt**:
```
This is the second file.
Merged content goes below the first file's content.
```

4. **locked_file.txt**: 
(Note: This file is locked or has permissions set to disallow reading. Contents cannot be displayed.)

---

## Privacy Disclosure

Welcome to GoatTool. We genuinely appreciate your trust and are firmly committed to preserving the privacy and security of your data. 

### Our Commitment:
*GoatTool*, while being a versatile command-line utility, is designed with the utmost care to respect your privacy. It operates primarily in your local environment, ensuring that your data stays where it belongs: with you.

### Data We Access:
1. **Files and Directories**: GoatTool may access your files and directories to perform its core functionalities. This is solely dependent on the commands you execute.
2. **Search Queries**: Queries you use for searching within files are processed, but not stored or transmitted.
3. **Encryption Passwords**: If you employ encryption features, the passwords are utilized for that specific purpose alone and are neither stored nor transmitted elsewhere.

### What We Do Not Do:
- GoatTool will never transmit or share your data with external servers or third parties.
- We do not integrate with or use third-party services that might jeopardize your privacy.
- Data is not sent over networks unless you explicitly command the tool to do so.

### Your Responsibility:
We urge you to exercise caution when providing sensitive information or credentials, especially while scripting or performing automated tasks with GoatTool. Always ensure you are only feeding the necessary and appropriate data for your tasks.

### Conclusion:
Your trust means everything to us. We want to ensure that while using GoatTool, you can focus on the tasks at hand without having to worry about privacy concerns. By using GoatTool, you acknowledge that you understand and consent to the practices detailed in this Privacy Disclosure.

Thank you for choosing GoatTool.

---
