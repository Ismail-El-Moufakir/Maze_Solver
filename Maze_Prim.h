#ifndef MAZE_PRIM
#define MAZE_PRIM
//constant
#define SCREEN_W 600
#define SCREEN_H 450
#define HEIGHT 300
#define WIDTH 300
#define CELL_W 30
#define CELL_H 30

//defining Cell Struct
typedef struct Cell
{
    int i;
    int j;
    int visited ;
    int In_Maze;
    int Walls[4];
}Cell ;
//defining Cell Struct
typedef struct Maze 
{
    int height ;
    int width ;
    Cell** MazeCells ;

}maze ;
//defining frontier Struct 
typedef struct Frontier 
{
    Cell cells[(HEIGHT*WIDTH)/(CELL_H*CELL_W)] ;
    int size ;
    

}Frontier; 

#endif //MAZE_PRIM