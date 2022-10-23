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

// Brute force matrix multiplication
void matrixMultiply(int **a, int **b, int **product, int sizeN); 

// Regular Divide and conquer algorithm
int **matixMultiplyDC(int **a, int **b, int start, int end);

// Straussen's Algorithm
int **matrixMultiplyStraussen(int **a, int **b, int sizeN);


#endif
