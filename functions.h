#ifndef FUNCTIONS_H
#define FUNCTIONS_H


// Matrix Creation functions
int getRandomNumber();
void deleteMatrix(int **a, int length);
void printMatrix(const std::vector<std::vector<int>>& vect, int length);
int **createEmptyMatrix(int n);
void createMatrix(std::vector<std::vector<int>>& vect, int n);

// Matrix Use cases
std::vector<std::vector<int>> partitionMatrix(const std::vector<std::vector<int>>& matrix, int rowStart, int rowEnd, int colStart, int colEnd);
void addMatrixStrauss(std::vector<std::vector<int>>& a, int aRowStart, int aRowEnd, int aColStart, int aColEnd, 
                                     std::vector<std::vector<int>>& b, int bRowStart, int bRowEnd, int bColStart, int bColEnd, 
                                     std::vector<std::vector<int>>& c, int cRowStart, int cRowEnd, int cColStart, int cColEnd, int size) ;
void subMatrixStrauss(std::vector<std::vector<int>>& a, int aRowStart, int aRowEnd, int aColStart, int aColEnd, 
                                     std::vector<std::vector<int>>& b, int bRowStart, int bRowEnd, int bColStart, int bColEnd, 
                                     std::vector<std::vector<int>>& c, int cRowStart, int cRowEnd, int cColStart, int cColEnd, int size);
int **subMatrices(int **a, int **b, int sizeN);
std::vector<std::vector<int>> combineMatrices(const std::vector<std::vector<int>>& quad1, const std::vector<std::vector<int>>&quad2, const std::vector<std::vector<int>>&quad3, const std::vector<std::vector<int>>&quad4, int sizeN);
std::vector<std::vector<int>> addMatrixStrauss(std::vector<std::vector<int>> a, std::vector<std::vector<int>> b, int size);

// Brute force matrix multiplication
std::vector<std::vector<int>> matrixMultiply(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b, int sizeN); 

// Regular Divide and conquer algorithm
std::vector<std::vector<int>> matrixMultiplyDC(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b);

// Straussen's Algorithm
void matrixMultiplyStraussen(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& c, int size);


#endif
