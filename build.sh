#!/bin/bash

# Set the compiler and compile flags
CC=gcc
CFLAGS="-Iinclude -Wall"

# Directories
SRCDIR=src
OBJDIR=obj
BINDIR=bin

# Target executable
TARGET="${BINDIR}/goattool"

# Function to compile source files into object files
compile() {
    mkdir -p "${OBJDIR}"
    for SRC_FILE in "${SRCDIR}"/*.c; do
        OBJ_FILE="${OBJDIR}/$(basename "${SRC_FILE}" .c).o"
        ${CC} ${CFLAGS} -c "${SRC_FILE}" -o "${OBJ_FILE}"
    done
}

# Function to link object files into the executable
link() {
    mkdir -p "${BINDIR}"
    OBJ_FILES=("${OBJDIR}"/*.o)
    ${CC} "${OBJ_FILES[@]}" -o "${TARGET}"
}

# Function to clean build files
clean() {
    rm -rf "${OBJDIR}" "${BINDIR}"
}

# Function to run tests
run_tests() {
    if [ -f "tests.sh" ]; then
        chmod +x tests.sh
        ./tests.sh
    else
        echo "tests.sh not found!"
    fi
}

# Main script logic
case $1 in
    clean)
        clean
        ;;
    *)
        compile && link && run_tests
        ;;
esac
