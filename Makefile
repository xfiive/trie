# compiler and it's flags
CC = gcc
CFLAGS = -Iinclude -Wall -Werror

# catalogs
SRCDIR = src 
OBJDIR = obj

# find a;; the .c files int /src and it's directories
SOURCES = $(shell find $(SRCDIR) -name '*.c')

# create proper names for .ob files in /obj
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# executable name
EXECUTABLE = main

# standart compilation rules
all: $(EXECUTABLE)

# object file compilation rule
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# .o and .c files compilation rule
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# cleaning rule
clean:
	rm -rf $(OBJDIR)/*.o $(EXECUTABLE)

# common rule for running a Makefile
.PHONY: all clean