#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Matrix Creation functions
int getRandomNumber();
void deleteMatrix(int **a, int length);
void printMatrix(int **a, int length);
int **createEmptyMatrix(int n);
int **createMatrix(int n);

// Brute force matrix multiplication
void matrixMultiply(int **a, int **b, int **product, int sizeN); 

// Regular Divide and conquer algorithm
int **matixMultiplyDivideAndConquer(int **a, int **b, int sizeN);

// Straussen's Algorithm
int **matrixMultiplyStraussen(int **a, int **b, int sizeN);


#endif
