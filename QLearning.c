#include "QLearning.h"
#include <stdlib.h>
#include <stdio.h>
#include "Maze_FDR.h"
#include "raylib.h"
#include "float.h"
//Q_Table Initialization
void Q_Table_Init(Q_Table* QT)
{
    //Initialize the Q-values (Q(s, a)) for all state-action pairs to 0 value
    for(int i = 0; i<CELLS_COUNT;i++)
    {
        for(int j = 0 ; j<ACTION_COUNT;j++)
        {
            QT->Q_Matrix[i][j] = 0 ;
        }
    }

}
//updating the Q table 
void Q_Learn_Update(Q_Table *QT, state s, action a, state s_next, double reward, double alpha, double gamma)
{
    int current_idx = s.i * COLS + s.j;
    int next_idx = s_next.i * COLS + s_next.j;
    int best_next_action = 0 ;
    double max_next_q = QT->Q_Matrix[next_idx][0];

    // Find the best next action
    for (int i = 1; i < ACTION_COUNT; i++) {
        if (QT->Q_Matrix[next_idx][i] > max_next_q) {
            max_next_q = QT->Q_Matrix[next_idx][i];
            best_next_action = i;
        }
    }

    // Update Q-Value using the Q-learning formula
    QT->Q_Matrix[current_idx][a.Direction] += alpha * (reward + gamma * max_next_q - QT->Q_Matrix[current_idx][a.Direction]);
}
action select_action(Q_Table *QT,state s, double epsilon)
{
    action a ;
    srand(time(NULL));
    double randomValue = rand() / (double)RAND_MAX;
    if(randomValue < epsilon)
    {   a.Direction = rand()%4 ;
        return a ;
    }
    else
    {
        int action_max = 0 ;
        int state_indx = s.i*COLS + s.j ;
        for(int i = 0 ; i<ACTION_COUNT;i++)
        {
             if(QT->Q_Matrix[state_indx][i]>QT->Q_Matrix[state_indx][action_max])
             {
                action_max = i ;
                a.Direction = action_max;
             }
        }
        return a ;
    }
}
state get_next_state(state s, action a, maze *M)
{
    state next_state = s; // Start with the current state as the next state
    Cell current_cell = M->MazeCells[s.i][s.j];

    switch (a.Direction) {
        case 0:
            if (s.i > 0 && current_cell.Walls[0] == 0) { // Check for no wall and boundary
                next_state.i -= 1;
            }
            break;
        case 1:
            if (s.i < ROWS - 1 && current_cell.Walls[1] == 0) { // Check for no wall and boundary
                next_state.i += 1;
            }
            break;
        case 2:
            if (s.j > 0 && current_cell.Walls[2] == 0) { // Check for no wall and boundary
                next_state.j -= 1;
            }
            break;
        case 3:
            if (s.j < COLS - 1 && current_cell.Walls[3] == 0) { // Check for no wall and boundary
                next_state.j += 1;
            }
            break;
    }

    return next_state;
}
double get_reward(state s, state s_next, maze *M)
{
    Cell c1 = M->MazeCells[s.i][s.j];
    Cell c2 = M->MazeCells[s_next.i][s_next.j];

    // Check if moved into a wall
    if (s.i == s_next.i && s.j == s_next.j) {
        printf("Hit a wall! Negative reward issued.\n");
       
        return -1.0;  
    }

    // Check if the goal is reached
    if (s_next.i == M->goal_i && s_next.j == M->goal_j) {
        printf("Goal reached! Positive reward issued.\n");
        return 10.0;  
    }

    // Penalty for revisiting the same cell 
    if (c2.visited) {
        printf("Revisited a cell! Slight penalty issued.\n");
        return -0.25;  
    }

    // Default reward for normal move
    return -0.1;  
}

int main()
{
    Cell c = {0,0,true,{1,1,1,1}};

    
    maze M;
     Create_Maze(&M,HEIGHT,WIDTH);
     M.MazeCells[0][0].visited = true;  // Start generation from the top-left corner
     Generate_Maze(&M, 0, 0);
     state s = {0,0};
}