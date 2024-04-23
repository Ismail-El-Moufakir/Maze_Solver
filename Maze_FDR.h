#ifndef MAZE_H
#define  MAZE_H
//constant
#define SCREEN_W 600
#define SCREEN_H 450
#define CELL_H 30
#define CELL_W 30
#define HEIGHT 300
#define WIDTH 300
//Cell Struct 
typedef struct Cell
{
    int i;
    int j;
    bool visited ;
    int Walls[4]; // 0 TOP 1 BOT 2 LEFT 3 RIGHT
    
}Cell ;
//Maz Struct
typedef struct Maze 
{
    int height ;
    int width ;
    Cell** MazeCells ;
    int goal_i;
    int goal_j ;

}maze ;
//Functions definition
void Create_Maze(maze* M,int height, int width);
void free_Maze(maze* M);
void Drawing_Maze(maze* M);
void Remove_Walls(Cell* c1, Cell* c2);
void Generate_Maze(maze *M, int row, int col);

#endif //MAZE_H