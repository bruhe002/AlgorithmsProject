#ifndef FUNCTIONS_H
#define FUNCTIONS_H


// Matrix Creation functions
int getRandomNumber();
void printMatrix(const std::vector<std::vector<int>>& vect, int length);
void createMatrix(std::vector<std::vector<int>>& vect, int n);

// Matrix Use cases
void addMatrix(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& c, int size);
void subMatrix(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& c, int size);

// Brute force matrix multiplication
std::vector<std::vector<int>> matrixMultiply(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b, int sizeN); 

// Regular Divide and conquer algorithm
std::vector<std::vector<int>> matrixMultiplyDC(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b);

// Straussen's Algorithm
void matrixMultiplyStraussen(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& c, int size);


#endif
