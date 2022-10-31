#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <array>

#include "functions.h"

using namespace std;

// Matrix Creation function
int getRandomNumber() {
    
    int randNum =  rand() % 9 + 1;

    return randNum;
}

void printMatrix(const vector<vector<int>>& vect, int length) {
    // cout << "Printing" << endl;
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < length; j++) {
            cout << vect[i][j] << " ";
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

void createMatrix(vector<vector<int>>& vect, int n) {
    
    for (int height = 0; height < n; height++) {
        for(int width = 0; width < n; width++) {
            vect[height][width] = getRandomNumber();
        }
    }

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

vector<vector<int>> partitionMatrix(const vector<vector<int>>& matrix, int rowStart, int rowEnd, int colStart, int colEnd) {
    // cout << "Error 1" << endl;
    int newSize = (colEnd - colStart) + 1;
    vector<vector<int>> newMatrix (newSize, vector<int> (newSize, 0));
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

void addMatrixStrauss(int**a, int**b, int aRow, int aCol, int bRow, int bCol, int size) {

}

void addMatrix(const vector<vector<int>>& a, const vector<vector<int>>& b, vector<vector<int>>& c, int sizeN) {
    for(int row = 0; row < sizeN; row++) {
        for(int col = 0; col < sizeN; col++) {
            c[row][col] = a[row][col] + b[row][col];
        }
    }
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

vector<vector<int>> combineMatrices(const vector<vector<int>>& quad1, const vector<vector<int>>& quad2, const vector<vector<int>>&quad3, const vector<vector<int>>&quad4, int sizeN) {
    // cout << "Entered combining functions" << endl;
    int newSize = sizeN * 2;
    vector<vector<int>> newMatrix(newSize, vector<int>(newSize, 0));
    // cout << "Started loop" << endl;
    for (int row = 0; row < newSize; row++) {
        // cout << "NEW ROW" << endl;
        for(int col = 0; col < newSize; col++) {
            // cout << "Adding element" << endl;
            if(row < sizeN) {
                if(col < sizeN) {
                    newMatrix[row][col] = quad1[row][col];
                }
                else {
                    newMatrix[row][col] = quad2[row][sizeN - (newSize - col)];
                }
            }
            else {
                if(col < sizeN) {
                    newMatrix[row][col] = quad3[sizeN - (newSize - row)][col];
                }
                else {
                    newMatrix[row][col] = quad4[sizeN - (newSize - row)][sizeN - (newSize - col)];
                }
            }

        }
    }

    return newMatrix;
}

// Brute force matrix multiplication
vector<vector<int>> matrixMultiply(const vector<vector<int>>& a, const vector<vector<int>>& b, int sizeN) {
    // For each row of matrix A, we must multiply with each column of matrix B
    vector<vector<int>> product (sizeN, vector<int> (sizeN, 0));
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
vector<vector<int>> matrixMultiplyDC(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    // Obtain sizes of vectors
    int aCols = a[0].size();
    int aRows = a.size();
    int bCols = b[0].size();
    int bRows = b.size();
    vector<vector<int>> returnMatrix(aRows, vector<int> (bCols, 0));

    if(aCols == 1) {
        
        returnMatrix[0][0] = a[0][0] * b[0][0]; 
    }
    else {
        int midPoint = bCols / 2;
        
        // Set up partitions
        vector<vector<int>> a11 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> a12 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> a21 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> a22 (midPoint, vector<int> (midPoint, 0));

        vector<vector<int>> b11 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> b12 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> b21 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> b22 (midPoint, vector<int> (midPoint, 0));

        vector<vector<int>> c11 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> c12 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> c21 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> c22 (midPoint, vector<int> (midPoint, 0));

        // Fill Partitions
        for(int row = 0; row < midPoint; row++) {
            for(int col = 0; col < midPoint; col++) {
                // Fill in A partitions
                a11[row][col] = a[row][col];
                a12[row][col] = a[row][col + midPoint];
                a21[row][col] = a[row + midPoint][col];
                a22[row][col] = a[row + midPoint][col + midPoint];

                // Fill in B Partitions
                b11[row][col] = b[row][col];
                b12[row][col] = b[row][col + midPoint];
                b21[row][col] = b[row + midPoint][col];
                b22[row][col] = b[row + midPoint][col + midPoint];
            }
        } 

        // a11 * b11 + a12 * b21
        // vector<vector<int>> productOne = matrixMultiplyDC(a, b, aRow, midPoint - 1, bRow, midPoint - 1, midPoint);
        // vector<vector<int>> productTwo = matrixMultiplyDC(a, b, aRow, midPoint, midPoint, bCol, midPoint);
        addMatrix(matrixMultiplyDC(a11, b11), matrixMultiplyDC(a12, b21), c11, midPoint);

        // a11 * b12 + a12 * b22
        addMatrix(matrixMultiplyDC(a11, b12), matrixMultiplyDC(a12, b22), c12, midPoint);

        // a21 * b11 + a22 * b21
        addMatrix(matrixMultiplyDC(a21, b11), matrixMultiplyDC(a22, b21), c21, midPoint);

        // a21 * b12 + a22 * b22
        addMatrix(matrixMultiplyDC(a21, b12), matrixMultiplyDC(a22, b22), c22, midPoint);

        //Combine the four quadrants
        for(int row = 0; row < midPoint; row++) {
            for(int col = 0; col < midPoint; col++) {
                //The combining is the reverse of the partition indexing 

                //First quadrant
                returnMatrix[row][col] = c11[row][col];
                //Second Quadrant
                returnMatrix[row][col + midPoint] = c12[row][col];
                //Third Quadrant
                returnMatrix[row + midPoint][col] = c21[row][col];
                //Fourth Quadrant
                returnMatrix[row + midPoint][col + midPoint] = c22[row][col];
            }
        }
        // vector<vector<int>> finalMatrix(combineMatrices(c11, c12, c21, c22, midPoint));
        a11.clear();
        a12.clear();
        a21.clear();
        a22.clear();
        b11.clear();
        b12.clear();
        b21.clear();
        b22.clear();
        c11.clear();
        c12.clear();
        c21.clear();
        c22.clear();
        
    }
    return returnMatrix;
}

// Straussen's Algorithm
// int **matrixMultiplyStraussen(int **a, int **b, int sizeN) {
//     // Create Midpoint
//     int midPoint = sizeN / 2;
//     // Base Case (divide and conquer)
//     if(sizeN == 1) {
//         // cout << a[0][0] << " " << b[0][0] << endl;
//         int **returnArray = new int *[1];
//         returnArray[0] = new int[1];
//         returnArray[0][0] = a[0][0] * b[0][0]; 
//         return returnArray;
//     }
//     else {
//         //Partition a & b matrices into their four quadrants
//         int **a11 = partitionMatrix(a, 0, midPoint - 1, 0, midPoint - 1);
//         int **a12 = partitionMatrix(a, 0, midPoint - 1, midPoint, sizeN - 1); 
//         int **a21 = partitionMatrix(a, midPoint, sizeN - 1, 0, midPoint - 1);
//         int **a22 = partitionMatrix(a, midPoint, sizeN - 1, midPoint, sizeN - 1);

//         int **b11 = partitionMatrix(b, 0, midPoint - 1, 0, midPoint - 1);
//         int **b12 = partitionMatrix(b, 0, midPoint - 1, midPoint, sizeN - 1);
//         int **b21 = partitionMatrix(b, midPoint, sizeN - 1, 0, midPoint - 1);
//         int **b22 = partitionMatrix(b, midPoint, sizeN - 1, midPoint, sizeN - 1);

//         // B12 - b22
//         int **sumOfProductOne = subMatrices(b12, b22, midPoint);
//         // B11 + B12
//         int **sumOfProductSeven2 = addMatrices(b11, b12, midPoint);
//         deleteMatrix(b12, midPoint);

//         // A11 + A12
//         int **sumOfProductTwo = addMatrices(a11, a12, midPoint);
//         // A12 - A22
//         int **sumOfProductSix1 = subMatrices(a12, a22, midPoint);
//         deleteMatrix(a12, midPoint);

//         // A21 + A22
//         int **sumOfProductThree = addMatrices(a21, a22, midPoint);
//         // A11 - A21
//         int **sumOfProductSeven1 = subMatrices(a11, a21, midPoint);
//         deleteMatrix(a21, midPoint);

//         // B21 - b11
//         int **sumOfProductFour = subMatrices(b21, b11, midPoint);
//         // B21 + B22
//         int **sumOfProductSix2 = addMatrices(b21, b22, midPoint);
//         deleteMatrix(b21, midPoint);

//         // A11 + A22
//         int **sumOfProductFive1 = addMatrices(a11, a22, midPoint);
//         int **productOne = matrixMultiplyStraussen(a11, sumOfProductOne, midPoint);
//         deleteMatrix(a11, midPoint);
//         deleteMatrix(sumOfProductOne, midPoint);
//         int **productFour = matrixMultiplyStraussen(a22, sumOfProductFour, midPoint);
//         deleteMatrix(a22, midPoint);
//         deleteMatrix(sumOfProductFour, midPoint);

//         // B11 + B22
//         int **sumOfProductFive2 = addMatrices(b11, b22, midPoint);
//         int **productThree = matrixMultiplyStraussen(sumOfProductThree, b11, midPoint);
//         deleteMatrix(b11, midPoint);
//         deleteMatrix(sumOfProductThree, midPoint);
//         int **productTwo = matrixMultiplyStraussen(sumOfProductTwo, b22, midPoint);
//         deleteMatrix(b22, midPoint);
//         deleteMatrix(sumOfProductTwo, midPoint);
        
//         int **productFive = matrixMultiplyStraussen(sumOfProductFive1, sumOfProductFive2, midPoint);
//         deleteMatrix(sumOfProductFive1, midPoint);
//         deleteMatrix(sumOfProductFive2, midPoint);

//         int **productSix = matrixMultiplyStraussen(sumOfProductSix1, sumOfProductSix2, midPoint);
//         deleteMatrix(sumOfProductSix1, midPoint);
//         deleteMatrix(sumOfProductSix2, midPoint);

//         int **productSeven = matrixMultiplyStraussen(sumOfProductSeven1, sumOfProductSeven2, midPoint);
//         deleteMatrix(sumOfProductSeven1, midPoint);
//         deleteMatrix(sumOfProductSeven2, midPoint);
        
//         // Add the Products
//         // P4 + P5
//         int **sumForFinalProduct45 = addMatrices(productFour, productFive, midPoint);

//         // P4 + P5 + P6
//         int **sumForFinalProduct456 = addMatrices(sumForFinalProduct45, productSix, midPoint);
//         deleteMatrix(sumForFinalProduct45, midPoint);

//         // P4 + P5 + P6 - P2
//         int **c11 = subMatrices(sumForFinalProduct456, productTwo, midPoint);

//         // int **c11 = addMatrices(subMatrices(addMatrices(productFive, productFour, midPoint), productTwo, midPoint), productSix, midPoint);
//         int **c12 = addMatrices(productOne, productTwo, midPoint);
//         deleteMatrix(productTwo, midPoint);

//         int **c21 = addMatrices(productThree, productFour, midPoint);
//         deleteMatrix(productFour, midPoint);

//         // P1 + P5
//         int **sumForFinalProduct15 = addMatrices(productOne, productFive, midPoint);
//         deleteMatrix(productOne, midPoint);
//         deleteMatrix(productFive, midPoint);

//         // P1 + P5 - P3
//         int **sumForFinalProduct153 = subMatrices(sumForFinalProduct15, productThree, midPoint);
//         deleteMatrix(sumForFinalProduct15, midPoint);
//         deleteMatrix(productThree, midPoint);

//         // P1 + P5 - P3 - P7
//         int **c22 = subMatrices(sumForFinalProduct153, productSeven, midPoint);
//         deleteMatrix(sumForFinalProduct153, midPoint);
//         deleteMatrix(productSeven, midPoint);

//         // Combine C products
//         int **finalProduct = combineMatrices(c11, c12, c21, c22, midPoint);

//         // Delete Pointers
//         deleteMatrix(c11, midPoint);
//         deleteMatrix(c12, midPoint);
//         deleteMatrix(c21, midPoint);
//         deleteMatrix(c22, midPoint);

//         // Return final Array
//         return finalProduct;

    // }
    

// }

