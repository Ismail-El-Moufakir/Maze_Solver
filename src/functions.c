#include "functions.h"

int min(int a, int b){
    return (a>b) ? b : a;
}

int max(int a, int b){
    return (a>b) ? a : b;
}

float maxL(float* L){
    float max = L[0];
    int i = 0;
    while(L[i] != '\0'){
        if (L[i] > max){
            max = L[i];
        }
        i++;
    }

    return max;
}

int maxI(float* L){
    int max = 0;
    int i = 0;
    while(L[i] != '\0'){
        if (L[i] > L[max]){
            max = i;
        }
        i++;
    }

    return max;
}