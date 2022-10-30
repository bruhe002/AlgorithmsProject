#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

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
    int **newArray2D = new int *[n];
    for(int i = 0; i < n; i++) {
        newArray2D[i] = new int[n];
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
int **matrixMultiply(int **a, int **b, int sizeN) {
    // For each row of matrix A, we must multiply with each column of matrix B
    int** product = createEmptyMatrix(sizeN);
    for(int rowA = 0; rowA < sizeN; rowA++) {
        for(int colB = 0; colB < sizeN; colB++) {
            int total = 0;
            for(int idx = 0; idx  < sizeN; idx++) {
                total += (a[rowA][idx] * b[idx][colB]);
            }
            product[rowA][colB] = total;
        }
    }

    return product; 
}

// Regular Divide and conquer algorithm
int **matrixMultiplyDC(int **a, int **b, int sizeN) {
    if(sizeN == 1) {
        // cout << a[0][0] << " " << b[0][0] << endl;
        int **returnArray = new int *[1];
        returnArray[0] = new int[1];
        returnArray[0][0] = a[0][0] * b[0][0]; 
        return returnArray;
    }
    else {
        int midPoint = sizeN/2;
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

        // a11 * b11 + a12 * b21
        int **productOne = matrixMultiplyDC(a11, b11, midPoint);
        int **productTwo = matrixMultiplyDC(a12, b21, midPoint);
        int **c11 = addMatrices(productOne, productTwo, midPoint);
        deleteMatrix(productOne, midPoint);
        deleteMatrix(productTwo, midPoint);

        // a11 * b12 + a12 * b22
        int **productThree = matrixMultiplyDC(a11, b12, midPoint);
        int **productFour = matrixMultiplyDC(a12, b22, midPoint);
        int **c12 = addMatrices(productThree, productFour, midPoint);
        deleteMatrix(a11, midPoint);
        deleteMatrix(a12, midPoint);
        deleteMatrix(productThree, midPoint);
        deleteMatrix(productFour, midPoint);

        // a21 * b11 + a22 * b21
        int **productFive = matrixMultiplyDC(a21, b11, midPoint);
        int **productSix = matrixMultiplyDC(a22, b21, midPoint);
        int **c21 = addMatrices(productFive, productSix, midPoint);
        deleteMatrix(b11, midPoint);
        deleteMatrix(b21, midPoint);
        deleteMatrix(productFive, midPoint);
        deleteMatrix(productSix, midPoint);

        // a21 * b12 + a22 * b22
        int **productSeven = matrixMultiplyDC(a21, b12, midPoint);
        int **productEight = matrixMultiplyDC(a22, b22, midPoint);
        int **c22 = addMatrices(productSeven, productEight, midPoint);
        deleteMatrix(a21, midPoint);
        deleteMatrix(a22, midPoint);
        deleteMatrix(b12, midPoint);
        deleteMatrix(b22, midPoint);
        deleteMatrix(productSeven, midPoint);
        deleteMatrix(productEight, midPoint);

        // Partition and add maticies using recursion
        
        // int **c11 =
        // int **c12 = addMatrices(, matrixMultiplyDC(a12, b22, midPoint), midPoint);
        // deleteMatrix(a11, midPoint);
        // deleteMatrix(a12, midPoint);
        //  addMatrices(matrixMultiplyDC(a21, b11, midPoint), matrixMultiplyDC(a22, b21, midPoint), midPoint);
        // int **c22 = addMatrices(matrixMultiplyDC(a21, b12, midPoint), matrixMultiplyDC(a22, b22, midPoint), midPoint);

        // //Delete unused matricies
        // deleteMatrix(a21, midPoint);
        // deleteMatrix(a22, midPoint);
        // deleteMatrix(b11, midPoint);
        // deleteMatrix(b12, midPoint);
        // deleteMatrix(b21, midPoint);
        // deleteMatrix(b22, midPoint);

        //Combine the four quadrants
        int **finalProduct = combineMatrices(c11, c12, c21, c22, midPoint);

        // Delete Everything
        
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

        // B12 - b22
        int **sumOfProductOne = subMatrices(b12, b22, midPoint);

        // A11 + A12
        int **sumOfProductTwo = addMatrices(a11, a12, midPoint);

        // A21 + A22
        int **sumOfProductThree = addMatrices(a21, a22, midPoint);

        // B21 - b11
        int **sumOfProductFour = subMatrices(b21, b11, midPoint);

        // A11 + A22
        int **sumOfProductFive1 = addMatrices(a11, a22, midPoint);

        // B11 + B22
        int **sumOfProductFive2 = addMatrices(b11, b22, midPoint);

        // A12 - A22
        int **sumOfProductSix1 = subMatrices(a12, a22, midPoint);

        // B21 + B22
        int **sumOfProductSix2 = addMatrices(b21, b22, midPoint);

        // A11 - A21
        int **sumOfProductSeven1 = subMatrices(a11, a21, midPoint);

        // B11 + B12
        int **sumOfProductSeven2 = addMatrices(b11, b12, midPoint);

        deleteMatrix(a12, midPoint);
        deleteMatrix(a21, midPoint);
        deleteMatrix(b12, midPoint);
        deleteMatrix(b21, midPoint);

        // Create Prodcut Matrices
        int **productOne = matrixMultiplyStraussen(a11, sumOfProductOne, midPoint);
        deleteMatrix(a11, midPoint);
        deleteMatrix(sumOfProductOne, midPoint);
        
        int **productTwo = matrixMultiplyStraussen(sumOfProductTwo, b22, midPoint);
        deleteMatrix(b22, midPoint);
        deleteMatrix(sumOfProductTwo, midPoint);

        int **productThree = matrixMultiplyStraussen(sumOfProductThree, b11, midPoint);
        deleteMatrix(b11, midPoint);
        deleteMatrix(sumOfProductThree, midPoint);

        int **productFour = matrixMultiplyStraussen(a22, sumOfProductFour, midPoint);
        deleteMatrix(a22, midPoint);
        deleteMatrix(sumOfProductFour, midPoint);

        int **productFive = matrixMultiplyStraussen(sumOfProductFive1, sumOfProductFive2, midPoint);
        deleteMatrix(sumOfProductFive1, midPoint);
        deleteMatrix(sumOfProductFive2, midPoint);

        int **productSix = matrixMultiplyStraussen(sumOfProductSix1, sumOfProductSix2, midPoint);
        deleteMatrix(sumOfProductSix1, midPoint);
        deleteMatrix(sumOfProductSix2, midPoint);

        int **productSeven = matrixMultiplyStraussen(sumOfProductSeven1, sumOfProductSeven2, midPoint);
        deleteMatrix(sumOfProductSeven1, midPoint);
        deleteMatrix(sumOfProductSeven2, midPoint);
        
        // Add the Products
        // P4 + P5
        int **sumForFinalProduct45 = addMatrices(productFour, productFive, midPoint);

        // P4 + P5 + P6
        int **sumForFinalProduct456 = addMatrices(sumForFinalProduct45, productSix, midPoint);
        deleteMatrix(sumForFinalProduct45, midPoint);

        // P4 + P5 + P6 - P2
        int **c11 = subMatrices(sumForFinalProduct456, productTwo, midPoint);

        // int **c11 = addMatrices(subMatrices(addMatrices(productFive, productFour, midPoint), productTwo, midPoint), productSix, midPoint);
        int **c12 = addMatrices(productOne, productTwo, midPoint);
        deleteMatrix(productTwo, midPoint);

        int **c21 = addMatrices(productThree, productFour, midPoint);
        deleteMatrix(productFour, midPoint);

        // P1 + P5
        int **sumForFinalProduct15 = addMatrices(productOne, productFive, midPoint);
        deleteMatrix(productOne, midPoint);
        deleteMatrix(productFive, midPoint);

        // P1 + P5 - P3
        int **sumForFinalProduct153 = subMatrices(sumForFinalProduct15, productThree, midPoint);
        deleteMatrix(sumForFinalProduct15, midPoint);
        deleteMatrix(productThree, midPoint);

        // P1 + P5 - P3 - P7
        int **c22 = subMatrices(sumForFinalProduct153, productSeven, midPoint);
        deleteMatrix(sumForFinalProduct153, midPoint);
        deleteMatrix(productSeven, midPoint);

        // Combine C products
        int **finalProduct = combineMatrices(c11, c12, c21, c22, midPoint);

        // Delete Pointers
        deleteMatrix(c11, midPoint);
        deleteMatrix(c12, midPoint);
        deleteMatrix(c21, midPoint);
        deleteMatrix(c22, midPoint);

        // Return final Array
        return finalProduct;

    }
    

}

