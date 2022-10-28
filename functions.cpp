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
    // cout << "Printing" << endl;
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

    return newArray2D;
}

int **createMatrix(int n) {
    
    int **tempArray2D = new int*[n];

    for (int height = 0; height < n; height++) {
        tempArray2D[height] = new int[n];

        for(int width = 0; width < n; width++) {
            tempArray2D[height][width] = getRandomNumber();
        }
    }

    return tempArray2D;
}


// USE CASES involving Arrays
void deleteMatrix(int **a, int length) {
    for(int i = 0; i < length; i++) {
        delete [] a[i];
        a[i] = nullptr;
    }

    delete [] a;
    a = nullptr;
}

int **partitionMatrix(int **matrix, int rowStart, int rowEnd, int colStart, int colEnd) {
    // cout << "Error 1" << endl;
    int newSize = (colEnd - colStart) + 1;
    int **newMatrix = createEmptyMatrix(newSize);
    int i = 0;
    int j = 0;
    int rowTemp = rowStart;
    int colTemp = 0;
    while(rowTemp <= rowEnd) {
        // cout << "MAKING MATRIX" << endl;
        j = 0;
        colTemp = colStart;
        while(colTemp <= colEnd) {
            // cout << "Filling matrix" << endl;
            newMatrix[i][j] = matrix[rowTemp][colTemp];
            colTemp++;
            j++;
        }
        rowTemp++;
        i++;
    }
    // cout << "Bout to return" << endl;
    return newMatrix; 
}

int** addMatrices(int **a, int **b, int sizeN) {
    int **newArray = createEmptyMatrix(sizeN);

    for(int row = 0; row < sizeN; row++) {
        for(int col = 0; col < sizeN; col++) {
            newArray[row][col] = a[row][col] + b[row][col];
        }
    }

    return newArray;
}

int** subMatrices(int **a, int **b, int sizeN) {
    int **newArray = createEmptyMatrix(sizeN);

    for(int row = 0; row < sizeN; row++) {
        for(int col = 0; col < sizeN; col++) {
            newArray[row][col] = a[row][col] - b[row][col];
        }
    }

    return newArray;
}

int** combineMatrices(int **quad1, int **quad2, int **quad3, int **quad4, int sizeN) {
    // cout << "Entered combining functions" << endl;
    int newSize = sizeN * 2;
    int **newArray = createEmptyMatrix(newSize);
    // cout << "Started loop" << endl;
    for (int row = 0; row < newSize; row++) {
        // cout << "NEW ROW" << endl;
        for(int col = 0; col < newSize; col++) {
            // cout << "Adding element" << endl;
            if(row < sizeN) {
                if(col < sizeN) {
                    newArray[row][col] = quad1[row][col];
                }
                else {
                    newArray[row][col] = quad2[row][sizeN - (newSize - col)];
                }
            }
            else {
                if(col < sizeN) {
                    newArray[row][col] = quad3[sizeN - (newSize - row)][col];
                }
                else {
                    newArray[row][col] = quad4[sizeN - (newSize - row)][sizeN - (newSize - col)];
                }
            }

        }
    }

    return newArray;
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
int **matrixMultiplyDC(int **a, int **b, int sizeN) {
    int midPoint = sizeN/2;
    if(sizeN == 1) {
        // cout << a[0][0] << " " << b[0][0] << endl;
        int **returnArray = new int *[1];
        returnArray[0] = new int[1];
        returnArray[0][0] = a[0][0] * b[0][0]; 
        return returnArray;
    }
    else {
        // Partition matrix A
        int **a11 = partitionMatrix(a, 0, midPoint - 1, 0, midPoint - 1);
        int **a12 = partitionMatrix(a, 0, midPoint - 1, midPoint, sizeN - 1); 
        int **a21 = partitionMatrix(a, midPoint, sizeN - 1, 0, midPoint - 1);
        int **a22 = partitionMatrix(a, midPoint, sizeN - 1, midPoint, sizeN - 1);

        // Partition matrix B
        int **b11 = partitionMatrix(b, 0, midPoint - 1, 0, midPoint - 1);
        int **b12 = partitionMatrix(b, 0, midPoint - 1, midPoint, sizeN - 1);
        int **b21 = partitionMatrix(b, midPoint, sizeN - 1, 0, midPoint - 1);
        int **b22 = partitionMatrix(b, midPoint, sizeN - 1, midPoint, sizeN - 1);

        // Partition matrix C
        int **c11 = addMatrices(matrixMultiplyDC(a11, b11, midPoint), matrixMultiplyDC(a12, b21, midPoint), midPoint);
        int **c12 = addMatrices(matrixMultiplyDC(a11, b12, midPoint), matrixMultiplyDC(a12, b22, midPoint), midPoint);
        int **c21 = addMatrices(matrixMultiplyDC(a21, b11, midPoint), matrixMultiplyDC(a22, b21, midPoint), midPoint);
        int **c22 = addMatrices(matrixMultiplyDC(a21, b12, midPoint), matrixMultiplyDC(a22, b22, midPoint), midPoint);

        //Combine the four quadrants
        int **finalProduct = combineMatrices(c11, c12, c21, c22, midPoint);

        // Delete Everything
        deleteMatrix(a11, midPoint);
        deleteMatrix(a12, midPoint);
        deleteMatrix(a21, midPoint);
        deleteMatrix(a22, midPoint);
        deleteMatrix(b11, midPoint);
        deleteMatrix(b12, midPoint);
        deleteMatrix(b21, midPoint);
        deleteMatrix(b22, midPoint);
        deleteMatrix(c11, midPoint);
        deleteMatrix(c12, midPoint);
        deleteMatrix(c21, midPoint);
        deleteMatrix(c22, midPoint);

        //Return the final product
        return finalProduct;

    }
}

// Straussen's Algorithm
int **matrixMultiplyStraussen(int **a, int **b, int sizeN) {
    // Create Midpoint
    int midPoint = sizeN / 2;
    // Base Case (divide and conquer)
    if(sizeN == 1) {
        // cout << a[0][0] << " " << b[0][0] << endl;
        int **returnArray = new int *[1];
        returnArray[0] = new int[1];
        returnArray[0][0] = a[0][0] * b[0][0]; 
        return returnArray;
    }
    else {
        //Partition a & b matrices into their four quadrants
        int **a11 = partitionMatrix(a, 0, midPoint - 1, 0, midPoint - 1);
        int **a12 = partitionMatrix(a, 0, midPoint - 1, midPoint, sizeN - 1); 
        int **a21 = partitionMatrix(a, midPoint, sizeN - 1, 0, midPoint - 1);
        int **a22 = partitionMatrix(a, midPoint, sizeN - 1, midPoint, sizeN - 1);

        int **b11 = partitionMatrix(b, 0, midPoint - 1, 0, midPoint - 1);
        int **b12 = partitionMatrix(b, 0, midPoint - 1, midPoint, sizeN - 1);
        int **b21 = partitionMatrix(b, midPoint, sizeN - 1, 0, midPoint - 1);
        int **b22 = partitionMatrix(b, midPoint, sizeN - 1, midPoint, sizeN - 1);
    
        // Create Prodcut Matrices
        int **productOne = matrixMultiplyStraussen(a11, subMatrices(b12, b22, midPoint), midPoint);
        int **productTwo = matrixMultiplyStraussen(addMatrices(a11, a12, midPoint), b22, midPoint);
        int **productThree = matrixMultiplyStraussen(addMatrices(a21, a22, midPoint), b11, midPoint);
        int **productFour = matrixMultiplyStraussen(a22, subMatrices(b21, b11, midPoint), midPoint);
        int **productFive = matrixMultiplyStraussen(addMatrices(a11, a22, midPoint), addMatrices(b11, b22, midPoint), midPoint);
        int **productSix = matrixMultiplyStraussen(subMatrices(a12, a22, midPoint), addMatrices(b21, b22, midPoint), midPoint);
        int **productSeven = matrixMultiplyStraussen(subMatrices(a11, a21, midPoint), addMatrices(b11, b12, midPoint), midPoint);

        // Add the Products
        int **c11 = addMatrices(subMatrices(addMatrices(productFive, productFour, midPoint), productTwo, midPoint), productSix, midPoint);
        int **c12 = addMatrices(productOne, productTwo, midPoint);
        int **c21 = addMatrices(productThree, productFour, midPoint);
        int **c22 = subMatrices(subMatrices(addMatrices(productFive, productOne, midPoint), productThree, midPoint), productSeven, midPoint);

        // Combine C products
        int **finalProduct = combineMatrices(c11, c12, c21, c22, midPoint);

        // Delete Pointers
        deleteMatrix(a11, midPoint);
        deleteMatrix(a12, midPoint);
        deleteMatrix(a21, midPoint);
        deleteMatrix(a22, midPoint);
        deleteMatrix(b11, midPoint);
        deleteMatrix(b12, midPoint);
        deleteMatrix(b21, midPoint);
        deleteMatrix(b22, midPoint);
        deleteMatrix(productOne, midPoint);
        deleteMatrix(productTwo, midPoint);
        deleteMatrix(productThree, midPoint);
        deleteMatrix(productFour, midPoint);
        deleteMatrix(productFive, midPoint);
        deleteMatrix(productSix, midPoint);
        deleteMatrix(productSeven, midPoint);
        deleteMatrix(c11, midPoint);
        deleteMatrix(c12, midPoint);
        deleteMatrix(c21, midPoint);
        deleteMatrix(c22, midPoint);

        // Return final Array
        return finalProduct;

    }
    

}

