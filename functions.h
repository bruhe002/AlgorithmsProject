#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Matrix Creation functions
int getRandomNumber();
void deleteMatrix(int **a, int length);
void printMatrix(int **a, int length);
int **createEmptyMatrix(int n);
int **createMatrix(int n);

// Matrix Use cases
int **partitionMatrix(int **matrix, int rowStart, int rowEnd, int colStart, int colEnd);
int** addMatrices(int **a, int **b, int sizeN);
int** combineMatrices(int **quad1, int **quad2, int **quad3, int **quad4, int sizeN);

// Brute force matrix multiplication
void matrixMultiply(int **a, int **b, int **product, int sizeN); 

// Regular Divide and conquer algorithm
int **matrixMultiplyDC(int **a, int **b, int size);

// Straussen's Algorithm
int **matrixMultiplyStraussen(int **a, int **b, int sizeN);


#endif
