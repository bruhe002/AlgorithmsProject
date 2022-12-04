#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
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

void createMatrix(vector<vector<int>>& vect, int n) {
    
    for (int height = 0; height < n; height++) {
        for(int width = 0; width < n; width++) {
            vect[height][width] = getRandomNumber();
        }
    }

}


// USE CASES involving Arrays
void addMatrix(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& c, int sizeN) {
    for(int row = 0; row < sizeN; row++) {
        for(int col = 0; col < sizeN; col++) {
            c[row][col] = a[row][col] + b[row][col];
        }
    }
}

void subMatrix(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& c, int sizeN) {
    for(int row = 0; row < sizeN; row++) {
        for(int col = 0; col < sizeN; col++) {
            c[row][col] = a[row][col] - b[row][col];
        }
    }
}

bool powerOfTwo(int n) {
    while(n > 1){
        if (n % 2 != 0) {
            return false;
        }
        n = n / 2;
    }
    return true;

}

// Brute force matrix multiplication
vector<vector<int>> matrixMultiply(vector<vector<int>>& a, vector<vector<int>>& b, int sizeN) {
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
vector<vector<int>> matrixMultiplyDC(vector<vector<int>>& a, vector<vector<int>>& b, int sizeN) {
    if (!powerOfTwo(sizeN)) {
        // Not a power of 2
        // Found out the closest greater power of two
        int newExponent = ceil(log2(sizeN));
        // cout << newExponent << endl;
    
        //Create new size of matrix
        int newSize = pow(2, newExponent);
        // cout << newSize << endl;

        //Create an array of Zeroes with new size
        vector<int> padVect(newSize, 0);
        // Pad matrix rows
        for(int row = 0; row < sizeN; row++) {
            for(int i = sizeN; i < newSize; i++) {
                a[row].push_back(0);
                b[row].push_back(0);
                //Pad matrix columns
                a.push_back(padVect);
                b.push_back(padVect);
            }
        }
        
        cout << "Pass 1 loop" << endl;
        
        
        
        for(int i = sizeN; i < newSize; i++) {
            
            
        }
        // cout << "Pass loop 2" << endl;
        //Update new size of matrix
        sizeN = newSize;
        // cout << newSize << endl;
        padVect.clear();
        
    }
    // Create New Matrix
    vector<vector<int>> returnMatrix(sizeN, vector<int> (sizeN, 0));

    if(sizeN == 1) {
        
        returnMatrix[0][0] = a[0][0] * b[0][0]; 
    }
    else {
        int midPoint = sizeN / 2;
        
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
        addMatrix(matrixMultiplyDC(a11, b11, midPoint), matrixMultiplyDC(a12, b21, midPoint), c11, midPoint);

        // a11 * b12 + a12 * b22
        addMatrix(matrixMultiplyDC(a11, b12, midPoint), matrixMultiplyDC(a12, b22, midPoint), c12, midPoint);

        // a21 * b11 + a22 * b21
        addMatrix(matrixMultiplyDC(a21, b11, midPoint), matrixMultiplyDC(a22, b21, midPoint), c21, midPoint);

        // a21 * b12 + a22 * b22
        addMatrix(matrixMultiplyDC(a21, b12, midPoint), matrixMultiplyDC(a22, b22, midPoint), c22, midPoint);

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
    if (!powerOfTwo(size)) {
        // Not a power of 2
        // Found out the closest greater power of two
        double newExponent = ceil(log2(size));
        // cout << newExponent << endl;
    
        //Create new size of matrix
        int newSize = pow(2, newExponent);
        // Pad matrix rows
        for(int row = 0; row < size; row++) {
            for(int i = size; i < newSize; i++) {
                a[row].push_back(0);
                b[row].push_back(0);
                c[row].push_back(0);
            }
        }
        //Create an array of Zeroes with new size
        vector<int> padVect(newSize, 0);
        //Pad matrix columns
        for(int i = size; i < newSize; i++) {
            a.push_back(padVect);
            b.push_back(padVect);
            c.push_back(padVect);
        }
        //Update new size of matrix
        size = newSize;
        
    }
    
    if(size == 1) {
        c[0][0] = a[0][0] * b[0][0];
    }
    else {
        

        int midPoint = size / 2;

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
        subMatrix(b12, b22, bResult, midPoint);
        matrixMultiplyStraussen(a11, bResult, productOne, midPoint);
        
        // A11 + a12
        addMatrix(a11, a12, aResult, midPoint);
        matrixMultiplyStraussen(aResult, b22, productTwo, midPoint);
        
        // A21 + A22
        addMatrix(a21, a22, aResult, midPoint);
        matrixMultiplyStraussen(aResult, b11, productThree, midPoint);
        
        // B21 - B11
        subMatrix(b21, b11, bResult, midPoint);
        matrixMultiplyStraussen(a22, bResult, productFour, midPoint);
        
        // A11 + A22
        addMatrix(a11, a22, aResult, midPoint);
        // B11 + B22
        addMatrix(b11, b22, bResult, midPoint);
        matrixMultiplyStraussen(aResult, bResult, productFive, midPoint);
        
        // A12 - A22
        subMatrix(a12, a22, aResult, midPoint);
        // B21 + B22
        addMatrix(b21, b22, bResult, midPoint);
        matrixMultiplyStraussen(aResult, bResult, productSix, midPoint);
        
        // A11 - A21
        subMatrix(a11, a21, aResult, midPoint);
        // B11 + B12
        addMatrix(b11, b12, bResult, midPoint);
        matrixMultiplyStraussen(aResult, bResult, productSeven, midPoint);

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

        aResult.clear();
        bResult.clear();

        productOne.clear();
        productTwo.clear();
        productThree.clear();
        productFour.clear();
        productFive.clear();
        productSix.clear();
        productSeven.clear();

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
    // printMatrix(returnMatrix, size);
    // return returnMatrix;
}

