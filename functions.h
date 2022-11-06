#ifndef FUNCTIONS_H
#define FUNCTIONS_H


// Matrix Creation functions
int getRandomNumber();
void printMatrix(const std::vector<std::vector<int>>& vect, int length);
void createMatrix(std::vector<std::vector<int>>& vect, int n);

// Matrix Use cases
void addMatrix(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& c, int size);
void subMatrix(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& c, int size);
bool powerOfTwo(int n);

// Brute force matrix multiplication
std::vector<std::vector<int>> matrixMultiply(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b, int sizeN); 

// Regular Divide and conquer algorithm
std::vector<std::vector<int>> matrixMultiplyDC(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b, int sizeN);

// Straussen's Algorithm
void matrixMultiplyStraussen(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& c, int size);


#endif
