#include "functions.h"
#include <stdlib.h>
#include <time.h>

int min(int a, int b){
    return (a>b) ? b : a;
}

int max(int a, int b){
    return (a>b) ? a : b;
}

float maxL(float* L){
    float max = L[0];
    int i = 0;
    while(i<4){
        if (L[i] > max){
            max = L[i];
        }
        i++;
    }

    return max;
}

/*int maxI(float* L){
    int max = 0;
    int i = 0;
    while(L[i] != '\0'){
        if (L[i] > L[max]){
            max = i;
        }
        i++;
    }
    return max;
}*/

/*float maxL(float* L) {
    float max_value = L[0];
    int count = 1;
    int indices[4];
    indices[0] = 0;

    // Find the maximum value and collect all indices with this maximum value
    for (int i = 1; i < 4; i++) {
        if (L[i] > max_value) {
            max_value = L[i];
            indices[0] = i;
            count = 1;
        } else if (L[i] == max_value) {
            indices[count] = i;
            count++;
        }
    }
    srand(time(NULL));
    // Randomly select one of the indices windices[0] = 0;ith the maximum value
    int random_index = rand() % count;
    return L[indices[random_index]];
}*/

int maxI(float* L) {
    float max_value = L[0];
    int count = 1;
    int indices[4];
    indices[0] = 0;

    // Find the maximum value and collect all indices with this maximum value
    for (int i = 1; i < 4; i++) {
        if (L[i] > max_value) {
            max_value = L[i];
            indices[0] = i;
            count = 1;
        } else if (L[i] == max_value) {
            indices[count] = i;
            count++;
        }
    }
    
    // Randomly select one of the indices with the maximum value
    int random_index = rand() % count;
    return indices[random_index];
}