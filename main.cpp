#include <iostream>

#include "functions.h"

using namespace std;

int main() {
    // Needed for random number generator
    srand(time(NULL));
    // Matrix creation tests
    int nLength = 0;
    cout << "Please enter a positive number: ";
    cin >> nLength;
    cout << endl;
    
    int **matrixA = createMatrix(nLength);
    int **matrixB = createMatrix(nLength);
    int **testResult1 = createEmptyMatrix(nLength);
    matrixMultiply(matrixA, matrixB, testResult1, nLength);

    
    // int **matrixB = partitionMatrix(matrixA, 0, nLength/2 - 1, 0, nLength/2 - 1);
    // int **matrixC = partitionMatrix(matrixA, nLength/2, nLength - 1, 0, nLength/2 - 1);
    // int **matrixD = partitionMatrix(matrixA, 0, nLength/2 - 1, nLength/2, nLength - 1);
    // // cout << "Bout to begin" << endl;
    // int **matrixE = partitionMatrix(matrixA, nLength/2, nLength - 1, nLength/2, nLength - 1);
    // // int **productMatrix = createEmptyMatrix(nLength);
    
    cout << endl;
    cout << "Matrix 1: " << endl;
    printMatrix(matrixA, nLength);


    cout << endl;
    cout << "Matrix 2: " << endl;
    printMatrix(matrixB, nLength);

    cout << endl;
    cout << "Test Result 1:" << endl;
    printMatrix(testResult1, nLength);
    
    int **testResult2 = matrixMultiplyDC(matrixA, matrixB, nLength);
    cout << endl;
    cout << "Test Result 2:" << endl;
    printMatrix(testResult2, nLength);

    int **testResult3 = matrixMultiplyStraussen(matrixA, matrixB, nLength);
    cout << endl;
    cout << "Test Result 3: " << endl;
    printMatrix(testResult3, nLength);
    
    // cout << endl;
    // cout << "Multiplying Matrices..." << endl;
    // matrixMultiply(matrixA, matrixB, productMatrix, nLength);

    // cout << endl;
    // cout << "Product Matrix " << endl;
    // printMatrix(productMatrix, nLength);

    deleteMatrix(matrixA, nLength);   
    deleteMatrix(matrixB, nLength);
    deleteMatrix(testResult1, nLength);
    deleteMatrix(testResult2, nLength);
    deleteMatrix(testResult3, nLength);

    // deleteMatrix(productMatrix, nLength);

    cout << endl;
    system("Pause");
    return 0;
}