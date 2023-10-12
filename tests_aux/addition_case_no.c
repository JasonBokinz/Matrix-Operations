#include "../tests/unit_tests.h"
#include "global.h"

int main() { 
    int** M = initializeMatrix(3, 2, (int[]){ 2, 3, 1, 3, 4, 5});
    int** N = initializeMatrix(4, 2, (int[]){5, 6, 3, 3, 7, 2, 1,5});
    int** A_act = initializeMatrix(3, 2, (int[]){5, 6, 8, 5, 5,10});
    int D[6] = {3,2,4,2,3,2};
    Addition(M, N, A_act, D);
    freeMatrix(3, M); freeMatrix(4, N); freeMatrix(3, A_act);
    return 0;
}
