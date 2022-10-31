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

vector<vector<int>> addMatrixStrauss(vector<vector<int>> a, int aRowStart, int aRowEnd, int aColStart, int aColEnd, 
                                     vector<vector<int>> b, int bRowStart, int bRowEnd, int bColStart, int bColEnd, int size) {
    int aRowTemp = aRowStart;
    int bRowTemp = bRowStart;
    vector<vector<int>> tempMatrix(size, vector<int>(size, 0));                                    
    for(int row = 0; row < size; row++) {
        int aColTemp = aColStart;
        int bColTemp = bColStart;
        for(int col = 0; col < size; col++) {
            tempMatrix[row][col] = a[aRowTemp][aColTemp] + b[bRowTemp][bColTemp];
            aColTemp++;
            bColTemp++;
        }

        aRowTemp++;
        bRowTemp++;
    }

    return tempMatrix;
}

void addMatrix(const vector<vector<int>>& a, const vector<vector<int>>& b, vector<vector<int>>& c, int sizeN) {
    for(int row = 0; row < sizeN; row++) {
        for(int col = 0; col < sizeN; col++) {
            c[row][col] = a[row][col] + b[row][col];
        }
    }
}

vector<vector<int>> subMatrixStrauss(vector<vector<int>> a, int aRowStart, int aRowEnd, int aColStart, int aColEnd, 
                                     vector<vector<int>> b, int bRowStart, int bRowEnd, int bColStart, int bColEnd, int size) {
    
    int aRowTemp = aRowStart;
    int bRowTemp = bRowStart;
    vector<vector<int>> tempMatrix(size, vector<int>(size, 0));                                    
    for(int row = 0; row < size; row++) {
        int aColTemp = aColStart;
        int bColTemp = bColStart;
        for(int col = 0; col < size; col++) {
            tempMatrix[row][col] = a[aRowTemp][aColTemp] - b[bRowTemp][bColTemp];
            aColTemp++;
            bColTemp++;
        }

        aRowTemp++;
        bRowTemp++;
    }

    return tempMatrix;
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
vector<vector<int>> matrixMultiplyStraussen(vector<vector<int>>& a, int aRowStart, int aRowEnd, int aColStart, int aColEnd,
                                            vector<vector<int>>& b, int bRowStart, int bRowEnd, int bColStart, int bColEnd,
                                            vector<vector<int>>& c, int cRowStart, int cRowEnd, int cColStart, int cColEnd) {
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
        // vector<vector<int>>::iterator iter_row_a = a.begin();
        // vector<int>::iterator iter_a;
        // vector<vector<int>>::iterator iter_row_b;
        // vector<int>::iterator iter_b;

        // Set up partitions
        // vector<vector<int>> a11 (midPoint, vector<int> (midPoint, 0));
        // vector<vector<int>> a12 (midPoint, vector<int> (midPoint, 0));
        // vector<vector<int>> a21 (midPoint, vector<int> (midPoint, 0));
        // vector<vector<int>> a22 (midPoint, vector<int> (midPoint, 0));

        // vector<vector<int>> b11 (midPoint, vector<int> (midPoint, 0));
        // vector<vector<int>> b12 (midPoint, vector<int> (midPoint, 0));
        // vector<vector<int>> b21 (midPoint, vector<int> (midPoint, 0));
        // vector<vector<int>> b22 (midPoint, vector<int> (midPoint, 0));

        // for(int row = 0; row < midPoint; row++) {
        //     for(int col = 0; col < midPoint; col++) {
        //         a11[row][col] = a[row][col];
        //         a12[row][col] = a[row][col + midPoint];
        //         a21[row][col] = a[row + midPoint][col];
        //         a22[row][col] = a[row + midPoint][col + midPoint];

        //         b11[row][col] = b[row][col];
        //         b12[row][col] = b[row][col + midPoint];
        //         b21[row][col] = b[row + midPoint][col];
        //         b22[row][col] = b[row + midPoint][col + midPoint];
        //     }
        // }

        vector<vector<int>> sumOne = subMatrixStrauss(b, bRowStart, midPoint - 1, midPoint, bColEnd, b, midPoint, bRowEnd, midPoint, bColEnd, midPoint);
        vector<vector<int>> sumTwo = addMatrixStrauss(a, aRowStart, midPoint - 1, aColStart, midPoint - 1, a, aRowStart, midPoint - 1, midPoint, aColEnd, midPoint);
        vector<vector<int>> sumThree = addMatrixStrauss(a, midPoint, aRowEnd, aColStart, midPoint - 1, a, midPoint, aColEnd, midPoint, aColEnd, midPoint);
        vector<vector<int>> sumFour = subMatrixStrauss(b, midPoint, bRowEnd, bColStart, midPoint - 1, b, bRowStart, midPoint - 1, bColStart, midPoint - 1, midPoint);
        vector<vector<int>> sumFive = addMatrixStrauss(a, aRowStart, midPoint - 1, aColStart, midPoint - 1, a, midPoint, aRowEnd, midPoint, aColEnd, midPoint);
        vector<vector<int>> sumSix = subMatrixStrauss(b, bRowStart, midPoint - 1, bColStart, midPoint - 1, b, midPoint, bRowEnd, midPoint, bColEnd, midPoint);
        vector<vector<int>> sumSeven = subMatrixStrauss(a, aRowStart, midPoint - 1, midPoint, aColEnd, a, midPoint, aRowEnd, midPoint, aColEnd, midPoint);
        vector<vector<int>> sumEight = addMatrixStrauss(b, midPoint, bRowEnd, bColStart, midPoint - 1, b, midPoint, bRowEnd, midPoint, bColEnd, midPoint);
        vector<vector<int>> sumNine = subMatrixStrauss(a, aRowStart, midPoint - 1, aColStart, midPoint - 1, a, midPoint, aRowEnd, aColStart, midPoint - 1, midPoint);
        vector<vector<int>> sumTen = addMatrixStrauss(b, bRowStart, midPoint - 1, bColStart, midPoint - 1, b, bColStart, midPoint - 1, midPoint, bColEnd, midPoint);

        

        // vector<vector<int>> productOne(matrixMultiplyStraussen(a, aRowStart, midPoint - 1, aColStart, midPoint - 1, subMatrixStrauss(b12, b22, midPoint)));
        // vector<vector<int>> productTwo(matrixMultiplyStraussen(addMatrixStrauss(a11, a12, midPoint), b22));
        // vector<vector<int>> productThree(matrixMultiplyStraussen(addMatrixStrauss(a21, a22, midPoint), b11));
        // vector<vector<int>> productFour(matrixMultiplyStraussen(a22, subMatrixStrauss(b21, b11, midPoint)));
        // vector<vector<int>> productFive(matrixMultiplyStraussen(addMatrixStrauss(a11, a22, midPoint), addMatrixStrauss(b11, b22, midPoint)));
        // vector<vector<int>> productSix(matrixMultiplyStraussen(subMatrixStrauss(a12, a22, midPoint), addMatrixStrauss(b21, b22, midPoint)));
        // vector<vector<int>> productSeven(matrixMultiplyStraussen(subMatrixStrauss(a11, a21, midPoint), addMatrixStrauss(b11, b12, midPoint)));

        // vector<vector<int>> c11 (addMatrixStrauss(productSix, addMatrixStrauss(productFive, subMatrixStrauss(productFour, productTwo, midPoint), midPoint), midPoint));
        // matrixMultiplyStraussen()
        // vector<vector<int>> c12 (addMatrixStrauss(productOne, productTwo, midPoint));
        // vector<vector<int>> c21 (addMatrixStrauss(productThree, productFour, midPoint));
        // vector<vector<int>> c22 (addMatrixStrauss(productOne, subMatrixStrauss(productFive, subMatrixStrauss(productThree, productSeven, midPoint), midPoint), midPoint));

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
    }

    return returnMatrix;
}

