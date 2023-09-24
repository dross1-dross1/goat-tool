# Goat Tool Documentation

**Authors:**
- Jaret Smith
- Deautaun Ross
- Johan Olvera
- ChatGPT

---

## Table of Contents
1. [Introduction](#introduction)
2. [Command Switches](#command-switches)
3. [Usage Examples](#usage-examples)
4. [Functions](#functions)

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
