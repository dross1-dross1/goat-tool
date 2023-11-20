# Define the compiler to use
CC = gcc

# Define any compile-time flags. Here, we include the headers located in the 'include' directory
CFLAGS = -Iinclude

# Define the source directory and object file directory
SRCDIR = src
OBJDIR = obj

# Define the binary (executable) directory
BINDIR = bin

# Automatically find all source files (.c) in the source directory
SOURCES := $(wildcard $(SRCDIR)/*.c)

# For each source file, generate the corresponding object file name
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Define the target executable name
TARGET = $(BINDIR)/goattool

# Define how to build the target executable
$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)                  # Create the binary directory if it doesn't exist
	$(CC) $(OBJECTS) -o $@              # Compile all object files into the target executable

# Define how to build object files from source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)                  # Create the object directory if it doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@         # Compile each source file into an object file

# Define a 'clean' command to remove built files
clean:
	rm -rf $(OBJDIR) $(BINDIR)          # Remove the object and binary directories

# Declare 'clean' as a phony target to ensure it's always executed even if a file named 'clean' exists
.PHONY: clean
