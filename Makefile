# Define the compiler and the include path
CC=gcc
CFLAGS=-Iinclude -g -Wall

# Define your output executable and object files
EXE=src/QLearning
OBJ=src/QLearning.o src/dfs.o src/functions.o src/mazeEnv.o

# The first rule is the default when you just type 'make'
# This rule depends on the executable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

# Rule for creating object files from c files
# The '-c' flag compiles the source files to object files
src/QLearning.o: src/QLearning.c include/QLearning.h
	$(CC) $(CFLAGS) -c src/QLearning.c -o src/QLearning.o

src/dfs.o: src/dfs.c include/mazeEnv.h
	$(CC) $(CFLAGS) -c src/dfs.c -o src/dfs.o

src/functions.o: src/functions.c include/functions.h
	$(CC) $(CFLAGS) -c src/functions.c -o src/functions.o

src/mazeEnv.o: src/mazeEnv.c include/mazeEnv.h
	$(CC) $(CFLAGS) -c src/mazeEnv.c -o src/mazeEnv.o

# Clean rule for cleaning up the compiled files
clean:
	rm -f $(OBJ) $(EXE)
