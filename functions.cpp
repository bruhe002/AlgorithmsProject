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
    cout << endl;

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

void addMatrixStrauss(vector<vector<int>>& a, int aRowStart, int aRowEnd, int aColStart, int aColEnd, 
                                     vector<vector<int>>& b, int bRowStart, int bRowEnd, int bColStart, int bColEnd, 
                                     vector<vector<int>>& c, int cRowStart, int cRowEnd, int cColStart, int cColEnd, int size) {
    // vector<vector<int>> tempMatrix(size, vector<int>(size, 0));                                    
    for(int row = 0; row < size; row++) {
        for(int col = 0; col < size; col++) {
            c[cRowStart + row][cColStart + col] = a[aRowStart + row][aColStart + col] + b[bRowStart + row][bColStart + col];
        }

    }
}

void addMatrix(const vector<vector<int>>& a, const vector<vector<int>>& b, vector<vector<int>>& c, int sizeN) {
    for(int row = 0; row < sizeN; row++) {
        for(int col = 0; col < sizeN; col++) {
            c[row][col] = a[row][col] + b[row][col];
        }
    }
}

void subMatrix(const vector<vector<int>>& a, const vector<vector<int>>& b, vector<vector<int>>& c, int sizeN) {
    for(int row = 0; row < sizeN; row++) {
        for(int col = 0; col < sizeN; col++) {
            c[row][col] = a[row][col] - b[row][col];
        }
    }
}

void subMatrixStrauss(vector<vector<int>>& a, int aRowStart, int aRowEnd, int aColStart, int aColEnd, 
                                     vector<vector<int>>& b, int bRowStart, int bRowEnd, int bColStart, int bColEnd, 
                                     vector<vector<int>>& c, int cRowStart, int cRowEnd, int cColStart, int cColEnd, int size) {
    
    // vector<vector<int>> tempMatrix(size, vector<int>(size, 0));                                    
    for(int row = 0; row < size; row++) {
        for(int col = 0; col < size; col++) {
            c[cRowStart + row][cColStart + col] = a[aRowStart + row][aColStart + col] - b[bRowStart + row][bColStart + col];
        }

    }

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
    // printMatrix(returnMatrix, aCols);
    return returnMatrix;
}

// Straussen's Algorithm
void matrixMultiplyStraussen(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& c, int size) {
    // int aCols = a[0].size();
    // int aRows = a.size();
    // int bCols = b[0].size();
    // int bRows = b.size();
    vector<vector<int>> returnMatrix(size, vector<int> (size, 0));

    if(size == 1) {
        c[0][0] = a[0][0] * b[0][0];
    }
    else {
        int midPoint = size / 2;

        // vector<vector<int>> sumOne(midPoint, vector<int>(midPoint, 0));
        // vector<vector<int>> sumTwo(midPoint, vector<int>(midPoint, 0));
        // vector<vector<int>> sumThree(midPoint, vector<int>(midPoint, 0));
        // vector<vector<int>> sumFour(midPoint, vector<int>(midPoint, 0));
        // vector<vector<int>> sumFive(midPoint, vector<int>(midPoint, 0));
        // vector<vector<int>> sumSix(midPoint, vector<int>(midPoint, 0));
        // vector<vector<int>> sumSeven(midPoint, vector<int>(midPoint, 0));
        // vector<vector<int>> sumEight(midPoint, vector<int>(midPoint, 0));
        // vector<vector<int>> sumNine(midPoint, vector<int>(midPoint, 0));
        // vector<vector<int>> sumTen(midPoint, vector<int>(midPoint, 0));

        vector<vector<int>> aResult(midPoint, vector<int>(midPoint, 0));
        vector<vector<int>> bResult(midPoint, vector<int>(midPoint, 0));

        vector<vector<int>> productOne(midPoint, vector<int>(midPoint));
        vector<vector<int>> productTwo(midPoint, vector<int>(midPoint));
        vector<vector<int>> productThree(midPoint, vector<int>(midPoint));
        vector<vector<int>> productFour(midPoint, vector<int>(midPoint));
        vector<vector<int>> productFive(midPoint, vector<int>(midPoint));
        vector<vector<int>> productSix(midPoint, vector<int>(midPoint));
        vector<vector<int>> productSeven(midPoint, vector<int>(midPoint));
        vector<vector<int>> productEight(midPoint, vector<int>(midPoint));
        vector<vector<int>> productNine(midPoint, vector<int>(midPoint));
        vector<vector<int>> productTen(midPoint, vector<int>(midPoint));

        vector<vector<int>> c11(midPoint, vector<int>(midPoint));
        vector<vector<int>> c12(midPoint, vector<int>(midPoint));
        vector<vector<int>> c21(midPoint, vector<int>(midPoint));
        vector<vector<int>> c22(midPoint, vector<int>(midPoint));
        // Set up partitions
        vector<vector<int>> a11 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> a12 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> a21 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> a22 (midPoint, vector<int> (midPoint, 0));

        vector<vector<int>> b11 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> b12 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> b21 (midPoint, vector<int> (midPoint, 0));
        vector<vector<int>> b22 (midPoint, vector<int> (midPoint, 0));

        for(int row = 0; row < midPoint; row++) {
            for(int col = 0; col < midPoint; col++) {
                a11[row][col] = a[row][col];
                a12[row][col] = a[row][col + midPoint];
                a21[row][col] = a[row + midPoint][col];
                a22[row][col] = a[row + midPoint][col + midPoint];

                b11[row][col] = b[row][col];
                b12[row][col] = b[row][col + midPoint];
                b21[row][col] = b[row + midPoint][col];
                b22[row][col] = b[row + midPoint][col + midPoint];
            }
        }

        //B12 - B22
        // subMatrixStrauss(b, bRowStart, midPoint - 1, midPoint, bColEnd, b, midPoint, bRowEnd, midPoint, bColEnd, bResult, 0, midPoint - 1, 0, midPoint - 1, midPoint);
        subMatrix(b12, b22, bResult, midPoint);
        matrixMultiplyStraussen(a11, bResult, productOne, midPoint);
        
        // A11 + a12
        // addMatrixStrauss(a, aRowStart, midPoint - 1, aColStart, midPoint - 1, a, aRowStart, midPoint - 1, midPoint, aColEnd, aResult, 0, midPoint - 1, 0, midPoint - 1, midPoint);
        addMatrix(a11, a12, aResult, midPoint);
        matrixMultiplyStraussen(aResult, b22, productTwo, midPoint);
        
        // A21 + A22
        // addMatrixStrauss(a, midPoint, aRowEnd, aColStart, midPoint - 1, a, midPoint, aRowEnd, midPoint, aColEnd, aResult, 0, midPoint - 1, 0, midPoint - 1, midPoint);
        addMatrix(a21, a22, aResult, midPoint);
        matrixMultiplyStraussen(aResult, b11, productThree, midPoint);
        
        // B21 - B11
        //subMatrixStrauss(b, midPoint, bRowEnd, bColStart, midPoint - 1, b, bRowStart, midPoint - 1, bColStart, midPoint - 1, bResult, 0, midPoint - 1, 0, midPoint -1, midPoint);
        subMatrix(b21, b11, bResult, midPoint);
        matrixMultiplyStraussen(a22, bResult, productFour, midPoint);
        
        // A11 + A22
        //addMatrixStrauss(a, aRowStart, midPoint - 1, aColStart, midPoint - 1, a, midPoint, aRowEnd, midPoint, aColEnd, aResult, 0, midPoint - 1, 0, midPoint - 1, midPoint);
        addMatrix(a11, a22, aResult, midPoint);
        // B11 + B22
        //addMatrixStrauss(b, bRowStart, midPoint - 1, bColStart, midPoint - 1, b, midPoint, bRowEnd, midPoint, bColEnd, bResult, 0, midPoint - 1, 0, midPoint - 1, midPoint);
        addMatrix(b11, b22, bResult, midPoint);
        matrixMultiplyStraussen(aResult, bResult, productFive, midPoint);
        
        // A12 - A22
        //subMatrixStrauss(a, aRowStart, midPoint - 1, midPoint, aColEnd, a, midPoint, aRowEnd, midPoint, aColEnd, aResult, 0, midPoint - 1, 0, midPoint - 1, midPoint);
        subMatrix(a12, a22, aResult, midPoint);
        // B21 + B22
        //addMatrixStrauss(b, midPoint, bRowEnd, bColStart, midPoint - 1, b, midPoint, bRowEnd, midPoint, bColEnd, bResult, 0, midPoint - 1, 0, midPoint - 1, midPoint);
        addMatrix(b21, b22, bResult, midPoint);
        matrixMultiplyStraussen(aResult, bResult, productSix, midPoint);
        
        // A11 - A21
        //subMatrixStrauss(a, aRowStart, midPoint - 1, aColStart, midPoint - 1, a, midPoint, aRowEnd, aColStart, midPoint - 1, aResult, 0, midPoint - 1, 0, midPoint - 1, midPoint);
        subMatrix(a11, a21, aResult, midPoint);
        // B11 + B12
        //addMatrixStrauss(b, bRowStart, midPoint - 1, bColStart, midPoint - 1, b, bRowStart, midPoint - 1, midPoint, bColEnd, bResult, 0, midPoint - 1, 0, midPoint - 1, midPoint);
        addMatrix(b11, b12, bResult, midPoint);
        matrixMultiplyStraussen(aResult, bResult, productSeven, midPoint);
        
        // //A11 * sumOne
        
        // //sumTwo * B22
        // vector<vector<int>> productTwo = 
        // //sumThree * B11
        // vector<vector<int>> productThree = 
        // //A22 * sumFour
        // vector<vector<int>> productFour = 
        // //SumFive * sumSix
        // vector<vector<int>> productFive = 
        // //sumSeven * sumEight
        // vector<vector<int>> productSix = 
        // //sumNine * sumTen
        // vector<vector<int>> productSeven = 

        // Adding C11
        addMatrix(productSix, productFive, aResult, midPoint); 
        addMatrix(aResult, productFour, bResult, midPoint);
        subMatrix(bResult, productTwo, c11, midPoint);

        // Adding c12
        addMatrix(productOne, productTwo, c12, midPoint);

        //Adding C21
        addMatrix(productThree, productFour, c21, midPoint);

        // Adding C22
        addMatrix(productOne, productFive, aResult, midPoint); 
        subMatrix(aResult, productThree, bResult,  midPoint);
        subMatrix(bResult, productSeven, c22, midPoint);

        for(int row = 0; row < midPoint; row++) {
            for(int col = 0; col < midPoint; col++) {
                //The combining is the reverse of the partition indexing 

                //First quadrant
                c[row][col] = c11[row][col];
                //Second Quadrant
                c[row][col + midPoint] = c12[row][col];
                //Third Quadrant
                c[row + midPoint][col] = c21[row][col];
                //Fourth Quadrant
                c[row + midPoint][col + midPoint] = c22[row][col];
            }
        }

        // sumOne.clear();
        // sumTwo.clear();
        // sumThree.clear();
        // sumFour.clear();
        // sumFive.clear();
        // sumSix.clear();
        // sumSeven.clear();
        // sumEight.clear();
        // sumNine.clear();
        // sumTen.clear();

        aResult.clear();
        bResult.clear();

        productOne.clear();
        productTwo.clear();
        productThree.clear();
        productFour.clear();
        productFive.clear();
        productSix.clear();
        productSeven.clear();
        // matrixMultiplyStraussen()
        // vector<vector<int>> c12 (addMatrixStrauss(productOne, productTwo, midPoint));
        // vector<vector<int>> c21 (addMatrixStrauss(productThree, productFour, midPoint));
        // vector<vector<int>> c22 (addMatrixStrauss(productOne, subMatrixStrauss(productFive, subMatrixStrauss(productThree, productSeven, midPoint), midPoint), midPoint));


    }
    // printMatrix(returnMatrix, size);
    // return returnMatrix;
}

