//#include "QLearning.h"
#include "../include/mazeEnv.h"
#include "../include/functions.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

float** InitQ(){
    float** Q = malloc(rows*cols*sizeof(float*));
    for (int i = 0;i<rows*cols;i++){
        Q[i] = malloc(4*sizeof(float));
        for (int j = 0;j<4;j++){
            Q[i][j] = 0;
        }
    }
    return Q;
}

/*float Qvalue(float** Q,int row , int col ,action a){
    return Q[row*cols-col][a];
}*/


void Qrender(float** Q){
    for (int i=0; i<rows*cols; i++) {
        for (int j=0; j< number_actions; j++){
             printf("%f ", Q[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

action eps_greedy(float** Q , double eps , int row,int col){
    action a;
    srand(time(NULL));
    double randomValue = rand() / (double)RAND_MAX;
    if (randomValue < eps){
        a = rand()%4;
        return a;
    }
    else {
        a = maxI(Q[row*cols + col]);
        return a;
    }
}

action Boltzman(float** Q);

void Training(float** Q,float learning_rate,float discount_factor, double eps){
    int old_row = state_row;
    int old_col = state_col;

    init_visited();
    mazeEnv_reset();
    int step = 0;

    while ((state_row != goal_row) || (state_col != goal_col)){
        printf("\n Etape %d \n" , step);
        // saving state
        old_row = state_row;
        old_col = state_col;
        // Choosing a using policy derived from Q
        action a;
        a = eps_greedy(Q ,eps,state_row ,state_col);
        
        //Qrender(Q);
        // Take action , retrieve new state and reeward
        envOutput NewState = mazeEnv_step(a);
        int reward = NewState.reward;
        
                /*else {
                    reward = -1;
                }*/
        // Update Q(s,a)
        Q[state_row*cols + state_col][a] = Q[state_row*cols + state_col][a] + learning_rate*(reward+discount_factor*maxL(Q[state_row*cols + state_col])-Q[state_row*cols + state_col][a]);
        // updating current state
        if (Is_Wall() == 0){
            state_row = NewState.new_row;
            state_col = NewState.new_col;
        }
        else{
            state_row = old_row;
            state_col = old_col;
        }
        
        
        // Leave crumbs
        int* current = &visited[state_row][state_col];
        *current = crumb;
        // step += 1
        step++;

        //sleep(0.5);
        add_crumbs();
        mazeEnv_render();
        printf("state : (%d // %d)" , state_row,state_col);

        
    }

}


int main(){
   mazeEnv_make("../data/maze.txt");
   init_visited();

   printf("%d, %d \n", rows, cols);
   printf("number of actions :  %d \n", number_actions); 

   mazeEnv_render();
    // ***************************************
    int iter = 1000000;
    float learning_rate = 0.8;
    float discount_factor = 0.8;

    float eps0 = 0.8;
    float eps = eps0;

    float** Q = InitQ();
    Training(Q , learning_rate , discount_factor,eps);
    /*while (episode < 1000000){
        printf("%d \n" , episode);
        Training(Q , learning_rate , discount_factor,eps);
        printf("%d \n" , episode);
        episode++;
    }*/

    for(int i = 0; i<iter; i++){
        printf("itération %d avec epsilon = %f\n",i, eps);
        eps = -((eps0)/iter)*i + eps0;
        Training(Q , learning_rate , discount_factor,eps);
        printf("fin de l'itération %d\n",i);
    }
   // ******************************
   add_crumbs();
   mazeEnv_render();

   free(Q);
   return 0;
}