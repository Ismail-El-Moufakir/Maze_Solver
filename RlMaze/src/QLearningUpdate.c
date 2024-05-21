//#include "QLearning.h"
#include "../include/mazeEnv.h"
#include "../include/functions.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

float** InitQ(){
    float** Q = malloc(rows*cols*sizeof(float*));
    for (int i = 0; i < rows*cols; i++){
        Q[i] = malloc(4*sizeof(float));
        for (int j = 0; j < 4; j++){
            Q[i][j] = 0;
        }
    }
    return Q;
}

/*float Qvalue(float** Q,int row , int col ,action a){
    return Q[row*cols-col][a];
}*/

void Qrender(float** Q){
    for (int i = 0; i < rows*cols; i++) {
        for (int j = 0; j < number_actions; j++){
            printf("%f ", Q[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

action eps_greedy(float** Q, double eps, int row, int col){
    action a;
    
    double randomValue = rand() / (double)RAND_MAX;
    if (randomValue < eps){
        a = rand() % 4;
        return a;
    }
    else {
        a = maxI(Q[row*cols + col]);
        return a;
    }
}

action Boltzman(float** Q);

void Training(float** Q, float learning_rate, float discount_factor, double eps){
    int old_row = state_row;
    int old_col = state_col;

    init_visited();
    mazeEnv_reset();
    int step = 0;

    int sortie = 0;
    while (sortie == 0){
        old_row = state_row;
        old_col = state_col;

        action a;
        a = eps_greedy(Q, eps, state_row, state_col);

        envOutput NewState = mazeEnv_step(a);
        int reward = NewState.reward;

        if (Is_Wall() == 0){
            state_row = NewState.new_row;
            state_col = NewState.new_col;
        }
        else {
            state_row = old_row;
            state_col = old_col;
        }

        Q[old_row*cols + old_col][a] = Q[old_row*cols + old_col][a] + learning_rate * (reward + discount_factor * maxL(Q[state_row*cols + state_col]) - Q[old_row*cols + old_col][a]);

        step++;

        if ((state_row == goal_row) && (state_col == goal_col)){
            sortie = 1;
        }
    }
    printf("FOUUUUUUND\n");
}


void Show_Path(float** Q) {
    init_visited();
    mazeEnv_reset();
    state_row = start_row;
    state_col = start_col;

    while ((state_row != goal_row) || (state_col != goal_col)) {
        int* current = &visited[state_row][state_col];
        *current = crumb;

        action a = maxI(Q[state_row*cols + state_col]);

        envOutput NewState = mazeEnv_step(a);

        state_row = NewState.new_row;
        state_col = NewState.new_col;
    }
    int* current = &visited[state_row][state_col];
    *current = crumb;
}

int main(){
    srand(time(NULL));
    mazeEnv_make("../data/maze.txt");
    init_visited();

    printf("%d, %d \n", rows, cols);
    printf("number of actions :  %d \n", number_actions); 

    mazeEnv_render();
    // ***************************************
    int iter = 1000;
    float learning_rate = 0.1;
    float discount_factor = 0.9;

    float eps0 = 0.8;
    float eps = eps0;

    float** Q = InitQ();

    for(int i = 0; i < iter; i++){
        printf("\n itération %d avec epsilon = %f\n", i, eps);
        eps = -((eps0)/iter)*i + eps0;
        if (eps < 0.01) {
            eps = 0.01;
        }
        init_visited();
        mazeEnv_reset();
        Training(Q, learning_rate, discount_factor, eps);
        printf("\n fin de l'itération %d\n", i);
    }
    


    Show_Path(Q);  // Appel de la fonction pour afficher le chemin trouvé

    add_crumbs();
    mazeEnv_render();
    free(Q);

    return 0;
}
