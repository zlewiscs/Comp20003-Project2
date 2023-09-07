# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# Define libraries to be linked (for example -lm)
LDLIBS = -lm

# Define sets of source files and object files
SRC = src/data.c src/list.c src/dynamicArray.c src/main.c
# OBJ is the same as SRC, just replace .c with .o and prepend 'src/'
OBJ = $(patsubst src/%.c,src/%.o,$(SRC))

# Define the executable name(s)
EXE1 = dict2
EXE2 = dict3

all: $(EXE1) $(EXE2)

# The first target:
$(EXE1): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE1) $(OBJ) $(LDLIBS)

# The second target:
$(EXE2): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE2) $(OBJ) $(LDLIBS)

# Rule to build .o files from corresponding .c files
src/%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXE1) $(EXE2)