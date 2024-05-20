src/QLearning         : src/QLearning.o src/functions.o src/mazeEnv.o
	gcc -I include/ -g -o src/QLearning src/QLearning.o src/functions.o src/mazeEnv.o -Wall

src/QLearning.o       : src/QLearning.c  include/mazeEnv.h
	gcc -I include/ -g -o src/QLearning.o -c src/QLearning.c -Wall

src/functions.o : src/functions.c include/functions.h
	gcc -I include/ -g -o src/functions.o -c src/functions.c -Wall

src/mazeEnv.o   : src/mazeEnv.c include/mazeEnv.h
	gcc -I include/ -g -o src/mazeEnv.o -c src/mazeEnv.c -Wall

