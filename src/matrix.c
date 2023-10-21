#include "../include/global.h"

// This method will return the number of non-zero elements if the number of non-zero elements are equal to or less than m
// S will store the sparse matrix of M if it exists.
int SparseMatrix(int** M, int** S, int* D){
    int nonZero = 0, yDimension = *D++, xDimension = *D;
    int maxDimension = (xDimension > yDimension) ? xDimension : yDimension;
    // Checks to see if M can be sparsed first while keeping track of non-zero values.
    for (int i=0; i < yDimension; i++) {
        for (int j=0; j < xDimension; j++) {
            if (nonZero > maxDimension) {
                return -1;
            }
            else if ((*(*(M+i)+j)) != 0) {
                nonZero++;
            }
        }
    }
    // Creates the sparse matrix.
    int columnIndex = 0;
    for (int i=0; i < yDimension; i++) {
        for (int j=0; j < xDimension; j++) {
            if ((*(*(M+i)+j)) != 0) {
                (*(*(S)+columnIndex)) = i;
                (*(*(S+1)+columnIndex)) = j;
                (*(*(S+2)+columnIndex)) = (*(*(M+i)+j));
                columnIndex++;
            }
        }
    }
    // Returns the number of non-zero values stored in the sparse.
    return nonZero;
    //abort();
}
// Helper function used to find the minimum dimension
int min(int x, int y) {
    return (x < y) ? x : y;
}
// This method adds matrices M and N and stores the sum matrix in A.
// Returns an integer based on certain cases.
int Addition(int** M, int** N, int** A, int* D){
    // Store dimension value given to us from the D array
    int yDimensionM = *D++, xDimensionM = *D++;
    int yDimensionN = *D++, xDimensionN = *D++;
    int yDimensionA = *D++, xDimensionA = *D; 

    // Initialize A with zero values
    for (int i = 0; i < yDimensionA; i++) {
        for (int j = 0; j < xDimensionA; j++) {
            (*(*(A+i)+j)) = 0;
        }
    }
    int row = min(min(yDimensionM, yDimensionN), yDimensionA);
    int col = min(min(xDimensionM, xDimensionN), xDimensionA);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            (*(*(A+i)+j)) = (*(*(M+i)+j)) + (*(*(N+i)+j));
        }
    }
    // Potential Cases when M and N are compatible for matrix addition
    if ((yDimensionM == yDimensionN) && (xDimensionM == xDimensionN)) {
        // Normal Case
        if ((yDimensionA == yDimensionM) && (xDimensionA == xDimensionM)) {
            return 1;
        }
        // If A is not compatible, it is oversized enough to contain the actual result.
        else if ((yDimensionA >= yDimensionM) && (xDimensionA >= xDimensionM)) {
            return 2;
        }
        // If A is not compatible, not enough space to contain the whole result.
        else {
            return -3;
        }
    }
    // Potential Cases when M and N are NOT compatible for matrix addition, but we try anyway.
    else {
        // If A has enough space or dimension to hold the result of addition 
       if ((yDimensionA >= min(yDimensionM, yDimensionN)) && (xDimensionA >= min(xDimensionM, xDimensionN))) {
        return -1;
       }
       // If A does not have enough space or dimension.
       // A should hold the elements that overlap / intersect its dimension
       else {
        return -2;
       }
    }
    //abort();
}
// This method multiplies matrices M and N and stores the product matrix in A.
// Returns an integer based on certain cases.
int Multiplication(int** M, int** N, int** A, int* D){
    // Store dimension value given to us from the D array
    int yDimensionM = *D++, xDimensionM = *D++;
    int yDimensionN = *D++, xDimensionN = *D++;
    int yDimensionA = *D++, xDimensionA = *D; 

    // Initialize A with zero values
    for (int i = 0; i < yDimensionA; i++) {
        for (int j = 0; j < xDimensionA; j++) {
            (*(*(A+i)+j)) = 0;
        }
    }
    // Multiply the two matrices M & N and store the product in A
    // int row = min(yDimensionM, yDimensionA);
    // int col = min(xDimensionN, xDimensionA);
    // for (int i = 0; i < row; i++) {
    //     for (int j = 0; j < col; j++) {
    //         (*(*(A+i)+j)) = 0;
    //         for (int k = 0; k < col; k++) {
    //             (*(*(A+i)+j)) += (*(*(M+i)+k)) * (*(*(N+k)+j));
    //         }
    //     }
    // }
    //Filling the A matrix
    for (int i = 0; i < yDimensionA; i++) {
        for (int j = 0; j < xDimensionA; j++) {
            (*(*(A+i)+j)) = 0;
            if (i < yDimensionM && j < xDimensionN) {
                for (int k = 0; k < yDimensionM; k++) {
                    (*(*(A+i)+j)) += (*(*(M+i)+k)) * (*(*(N+k)+j));
                }
            }
        }
    }
    // Potential Cases when M and N are compatible for matrix multiplication.
    if (yDimensionM == xDimensionN) {
        // Normal Case
        if ((yDimensionA == yDimensionM) && (xDimensionA == xDimensionN)) {
            return 1;
        }
        // If A is not compatible, it is oversized enough to contain the actual result.
        else if ((yDimensionA >= yDimensionM) && (xDimensionA >= xDimensionN)) {
            return 2;
        }
        // If A is not compatible, not enough space to contain the whole result.
        else {
            return -3;
        }
    }
    // Potential Cases when M and N are NOT compatible for matrix multiplication, but we try anyway.
    else {
        // If A has enough space or dimension to hold the result of multiplication. 
       if ((yDimensionA >= min(yDimensionM, yDimensionN)) && (xDimensionA >= min(xDimensionM, xDimensionN))) {
        return -1;
       }
       // If A does not have enough space or dimension.
       // A should hold the elements that overlap / intersect its dimension
       else {
        return -2;
       }
    }
    //abort();
}
// This method transposes matrix A and stores it in AT.
// Returns an integer based on certain cases.
int Transpose(int** A, int** AT, int* D){
    // Store dimension value given to us from the D array
    int yDimensionA = *D++, xDimensionA = *D++;
    int yDimensionAT = *D++, xDimensionAT = *D;
    // Initialize AT with zero values
    for (int i = 0; i < yDimensionAT; i++) {
        for (int j = 0; j < xDimensionAT; j++) {
            (*(*(AT+i)+j)) = 0;
        }
    }
    // Transpose A values into AT
    int row = min(yDimensionA, xDimensionAT);
    int col = min(xDimensionA, yDimensionAT);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            (*(*(AT+j)+i)) = (*(*(A+i)+j));
        }
    }
    // If the dimension of A and AT are compatible
    if ((yDimensionA == xDimensionAT) && (xDimensionA == yDimensionAT)) {
        return 1;
    }
    // Potential Cases when A and AT are NOT compatible for matrix multiplication, but we try anyway.
    else {
        // If AT has enough space or dimension to hold the result of transpose.
        if ((yDimensionAT >= xDimensionA) && (xDimensionAT >= yDimensionA)) {
            return 2;
        }
        // If AT does not have enough space or dimension, then AT should hold the elements of transpose that overlap / intersect its dimension
        else {
            return -1;
        }
    }
    //abort();
}

// Helper functions for Testing
int** initializeMatrix(int n, int m, int* values){
    int** ret = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        ret[i] = (int*)malloc(m*sizeof(int));
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            ret[i][j] = values[i*m+j];
        }
    }
    return ret;
}
// Free storage
void freeMatrix(int n, int** M){
    for(int i=0; i<n; i++){
        free(M[i]);
    }
    free(M);
}