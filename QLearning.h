#ifndef QLEARNING
#define QLEARNING

//constants
#define HEIGHT 300
#define WIDTH 300
#define CELL_W 30
#define CELL_H 30
#define CELLS_COUNT HEIGHT*WIDTH/(CELL_H*CELL_W)
#define COLS WIDTH/CELL_W
#define ROWS HEIGHT/CELL_H

#define ACTION_COUNT 4 
//Q_Table struct 
typedef struct Q_Table
{
int Q_Matrix[CELLS_COUNT][4];
}Q_Table;
//state struct
typedef struct state
{
    int i ;
    int j ;
}state;

//Action Struct
typedef struct action
{
    int Direction; //0:up 1: Down 2: Left 3:right;
}action



#endif //QLEARNING