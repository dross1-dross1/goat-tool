# Define the compiler to use
CC = gcc

# Compiler flags:
# -Wall turns on most compiler warnings
# -g adds debugging information to the executable file
# -I adds include path for header files
CFLAGS = -Wall -g -Igoat-tool/include

# Define the source directory for .c files
SRCDIR = goat-tool/src

# Define the list of object files that will be compiled
OBJ = $(SRCDIR)/file_operations.o $(SRCDIR)/main.o $(SRCDIR)/search_and_compression.o

# Define the name of the final executable file
MAIN = goat-tool

# 'all' is the default target. It's conventionally used as the main build target.
# This target will call the $(MAIN) target by default when 'make' is run without arguments.
.PHONY: all
all: $(MAIN)
	@echo Compilation complete.

# Link the object files into the final executable
# Depends on the OBJ variable, which lists the object files
$(MAIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJ)

# Pattern rule for object files
# Compiles .c to .o; $< is the first prerequisite (the .c file)
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# 'clean' is a phony target that tells make how to clean up the workspace
# Removes all object files and the executable file
# The @ symbol before a command prevents make from printing the command to the terminal
.PHONY: clean
clean:
	@$(RM) $(SRCDIR)/*.o $(MAIN)
	@echo Cleanup complete.

# 'make clean' will invoke this target, which is used to clean the build artifacts.
