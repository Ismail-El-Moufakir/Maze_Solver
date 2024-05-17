#ifndef TIC_H
#define TIC_H
//Defining Constants
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define CELL_SIZE 200

#define ALPHA 0.1
#define GAMMA 0.9
#define EPSILON 0.1

typedef struct {
    int board[3][3];
    int currentPlayer;
} TicTacToe;

#endif //TIC_H