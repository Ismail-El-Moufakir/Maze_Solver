#include "raylib.h"
#include "Maze_FDR.h"
#include <stdlib.h>
#include <stdio.h>






//main function 
//Maze Create Function
void Create_Maze(maze* M,int height, int width)
{
   M->height = height;
   M->width = width;
   int rows  = height/CELL_H;
   int cols =  width/CELL_W;
   M->MazeCells = (Cell**)malloc(rows * sizeof(Cell*));
   if (M->MazeCells == NULL)
   {
      printf("MazeCells Rows Memory allocation error\n");
      exit(EXIT_FAILURE);  
   }

   for (int i = 0; i < rows; i++)
   {
      M->MazeCells[i] = (Cell*)malloc(cols * sizeof(Cell));
      if (M->MazeCells[i] == NULL)
      {
         printf("MazeCells Rows Memory allocation error\n");
         for (int j = 0; j < i; j++)
         {
            free(M->MazeCells[j]);  // Free previously allocated rows
         }
         free(M->MazeCells);  
         exit(EXIT_FAILURE);  
      }
   }

   for (int i = 0; i < rows; i++)
   {
      for (int j = 0; j < cols; j++)
      {
         Cell c = {i, j, false, {1, 1, 1, 1}};
         M->MazeCells[i][j] = c;  
      }
   }
}

//Maze free memory Function
void free_Maze(maze* M){
    int rows = M->height/CELL_H ; 
for(int i = 0 ; i<rows;i++)
{
    free(M->MazeCells[i]);
}
free(M->MazeCells);

}
//drawing Maze Function
void Drawing_Maze(maze* M)
{
    int rows  = M->height/CELL_H;
    int cols  = M->width/CELL_W ;
    for(int i = 0 ; i<rows -1; i++)
    {
        for(int j = 0 ; j<cols -1  ; j++)
        {
            if(M->MazeCells[i][j].visited == true)
            {
                Cell c = M->MazeCells[i][j];
                if(c.Walls[0] == 1){DrawLine(CELL_W*j,CELL_H*i,CELL_W*(j+1),CELL_H*i,BLACK);}
                if(c.Walls[1] == 1){DrawLine(CELL_W*j,CELL_H*(i+1),CELL_W*(j+1),CELL_H*(i+1),BLACK);}
                if(c.Walls[2] == 1){DrawLine(CELL_W*j,CELL_H*i,CELL_W*j,CELL_H*(i+1),BLACK);}
                if(c.Walls[3] == 1){DrawLine(CELL_W*(j+1),CELL_H*i,CELL_W*(j+1),CELL_H*(i+1),BLACK);}
            }            
        }
    }
}
//Remove Walls Function 
void Remove_Walls(Cell* c1, Cell* c2) {
    if (c2->i - c1->i == 1) { 
        c1->Walls[1] = 0; 
        c2->Walls[0] = 0; 
    } else if (c2->i - c1->i == -1) { 
        c1->Walls[0] = 0; 
        c2->Walls[1] = 0; 
    } else if (c2->j - c1->j == 1) { 
        c1->Walls[3] = 0; 
        c2->Walls[2] = 0; 
    } else if (c2->j - c1->j == -1) { 
        c1->Walls[2] = 0; 
        c2->Walls[3] = 0; 
    }
}
//Maze generation Function
void Generate_Maze(maze *M, int row, int col) {
    int rows = M->height / CELL_H;
    int cols = M->width / CELL_W;

    // Directions array for moving in the maze: [left, right, up, down]
    int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    
    for (int i = 0; i < 4; i++) {
        int j = GetRandomValue(i, 3);
        int temp[2] = {directions[i][0], directions[i][1]};
        directions[i][0] = directions[j][0];
        directions[i][1] = directions[j][1];
        directions[j][0] = temp[0];
        directions[j][1] = temp[1];
    }

  
    M->MazeCells[row][col].visited = true;

    
    for (int i = 0; i < 4; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !M->MazeCells[newRow][newCol].visited) {
            
            Remove_Walls(&M->MazeCells[row][col], &M->MazeCells[newRow][newCol]);
            
            Generate_Maze(M, newRow, newCol);
        }
    }
}


int main()
{
    int Cells_count = 0 ;
    Cell c = {0,0,true,{1,1,1,1}};
    //Configuring and initializing Raylib
    InitWindow(SCREEN_W,SCREEN_H,"Maze Solver");
    SetTargetFPS(60);
    
    maze M;
     Create_Maze(&M,HEIGHT,WIDTH);
     M.MazeCells[0][0].visited = true;  // Start generation from the top-left corner
     Generate_Maze(&M, 0, 0);
    
   
    while(!WindowShouldClose())
    {
        
        ClearBackground(WHITE);
        BeginDrawing();
        DrawRectangleLines(0,0,WIDTH,HEIGHT,BLACK);
        Drawing_Maze(&M);
        EndDrawing();
        
    }
    
    CloseWindow();
    free_Maze(&M);
  
}