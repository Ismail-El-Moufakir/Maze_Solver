#include "dfs.h"


int dfs(int row, int col){
    int* current = &visited[row][col];

    if(*current == goal){
        return 1;
    }else if(*current == unknown){
        *current = known;

        if (dfs(row, col-1)){
            *current = crumb;
            return 1;
        } else if (dfs(row+1, col)){
            *current = crumb;
            return 1;
        }  else if (dfs(row, col+1)){
            *current = crumb;
            return 1;
        }  else if (dfs(row-1, col)){
            *current = crumb;
            return 1;
        }

    }

    return 0;
}


int main(){
   mazeEnv_make("../data/maze.txt");
   init_visited();

   printf("%d, %d \n", rows, cols);
   printf("number of actions :  %d \n", number_actions); 
   mazeEnv_render();
   printf("11111 \n");
   dfs(start_row,start_col);
   printf("222222 \n");
   add_crumbs();
   printf("333333 \n");
   mazeEnv_render();
   printf("4444444 \n");
   return 0;
}

