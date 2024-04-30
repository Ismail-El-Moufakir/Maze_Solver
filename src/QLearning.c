#include "mazeEnv.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // pour utiliser la fonction sleep()

#define ALPHA 0.1     // Learning rate
#define GAMMA 0.9     // Discount factor
#define EPSILON 0.1   // Exploration rate
#define EPISODES 100  // nombre d'episode
#define DELAY_SECONDS 1 //retard en secondes pour l'affichage

float Q[100][100][4]; // initialisation statique de Q Table

void initialize_Q() {
    memset(Q, 0, sizeof(Q));
}

int choose_action(int row, int col) {
    if ((float)rand() / RAND_MAX < EPSILON) {
        // action aleatoire
        return rand() % number_actions;
    } else {
        // choisir meilleur action
        int best_action = 0;
        float best_value = Q[row][col][0];
        for (int a = 1; a < number_actions; a++) {
            if (Q[row][col][a] > best_value) {
                best_value = Q[row][col][a];
                best_action = a;
            }
        }
        return best_action;
    }
}
//mise a  jour du Q_Table
void update_Q(int s_row, int s_col, int action, int reward, int new_row, int new_col) {
    float max_q_new = Q[new_row][new_col][0];
    for (int a = 1; a < number_actions; a++) {
        if (Q[new_row][new_col][a] > max_q_new) {
            max_q_new = Q[new_row][new_col][a];
        }
    }
    Q[s_row][s_col][action] += ALPHA * (reward + GAMMA * max_q_new - Q[s_row][s_col][action]);
}

void run_episode() {
    int row = start_row, col = start_col;
    mazeEnv_reset();
    int steps = 0;  // pour eviter la boucle infinie

    while (1) {
        int chosen_action = choose_action(row, col);
        envOutput result = mazeEnv_step((action)chosen_action);
        int reward = result.reward;
        int new_row = result.new_row;
        int new_col = result.new_col;
        int done = result.done;

        // verifier que le nouvel etat n'est pas un mur
        if (mazeEnv[new_row][new_col] == '+') {  
            reward = -10; // penalité pour toucher un mur
            new_row = row; //rester en place
            new_col = col;
        } else {
            mazeEnv[row][col] = '.'; // marquer l'etat actuel (trajet)
        }

        update_Q(row, col, chosen_action, reward, new_row, new_col);
        mazeEnv_render(); // afficher l'etat actuel
        sleep(DELAY_SECONDS); // retard pour visualiser l'avancement de l'agent

        row = new_row;
        col = new_col;

        if (done) {
            mazeEnv[row][col] = 'G'; // marquer l'arrivée
            break;
        }

        if (++steps > 1000) { // test pour éviter la boucle infini
            break;
        }
    }
}

int main() {
    srand(time(NULL)); // generateur nombre aleatoire
    mazeEnv_make("../data/maze.txt");
    init_visited();
    initialize_Q();

    printf("%d, %d \n", rows, cols);
    printf("Number of actions: %d \n", number_actions); 
    for (int i = 0; i < EPISODES; i++) {
        printf("Episode %d:\n", i + 1);
        run_episode();  // lancer les episodes 
        mazeEnv_reset(); // reinstialiser le Labyrinthe
    }

    return 0;
}
