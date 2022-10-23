#include <iostream>
#include <cstdlib>
#include <ctime>

#include "functions.h"

using namespace std;

// Matrix Creation function
int getRandomNumber() {
    
    int randNum =  rand() % 9 + 1;

    return randNum;
}

void printMatrix(int **a, int length) {
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < length; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

}

int **createEmptyMatrix(int n) {
    int **newArray2D = new int*[n];
    for(int i = 0; i < n; i++) {
        newArray2D[i] = new int[n];

        for(int j = 0; j < n; j++) {
            newArray2D[i][j] = 0; 
        }
    }
}

int **createMatrix(int n) {
    srand(time(NULL));
    int **tempArray2D = new int*[n];

    for (int height = 0; height < n; height++) {
        tempArray2D[height] = new int[n];

        for(int width = 0; width < n; width++) {
            tempArray2D[height][width] = getRandomNumber();
        }
    }

    return tempArray2D;
}

void deleteMatrix(int **a, int length) {
    for(int i = 0; i < length; i++) {
        delete [] a[i];
    }

    delete [] a;
}

// Brute force matrix multiplication
void matrixMultiply(int **a, int **b, int **product, int sizeN) {
    // For each row of matrix A, we must multiply with each column of matrix B
    
    for(int rowA = 0; rowA < sizeN; rowA++) {
        for(int colB = 0; colB < sizeN; colB++) {
            int total = 0;
            for(int idx = 0; idx  < sizeN; idx++) {
                total += (a[rowA][idx] * b[idx][colB]);
            }
            product[rowA][colB] = total;
        }
    }
 
}

// Regular Divide and conquer algorithm
int **matixMultiplyDivideAndConquer(int **a, int **b, int sizeN) {

}

// Straussen's Algorithm
int **matrixMultiplyStraussen(int **a, int **b, int sizeN) {

}

