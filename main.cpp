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
    int **matrixB = partitionMatrix(matrixA, 0, nLength/2 - 1, 0, nLength/2 - 1);
    int **matrixC = partitionMatrix(matrixA, nLength/2, nLength - 1, 0, nLength/2 - 1);
    int **matrixD = partitionMatrix(matrixA, 0, nLength/2 - 1, nLength/2, nLength - 1);
    cout << "Bout to begin" << endl;
    int **matrixE = partitionMatrix(matrixA, nLength/2, nLength - 1, nLength/2, nLength - 1);
    // int **productMatrix = createEmptyMatrix(nLength);
    
    cout << endl;
    cout << "Matrix 1: " << endl;
    printMatrix(matrixA, nLength);
    deleteMatrix(matrixA, nLength);

    cout << endl;
    cout << "Matrix 2: " << endl;
    printMatrix(matrixB, nLength/2);

    cout << endl;
    cout << "Matrix 3: " << endl;
    printMatrix(matrixC, nLength/2);

    cout << endl;
    cout << "Matrix 4: " << endl;
    printMatrix(matrixD, nLength/2);

    cout << endl;
    cout << "Matrix 5: " << endl;
    printMatrix(matrixE, nLength/2);
    
    // cout << endl;
    // cout << "Multiplying Matrices..." << endl;
    // matrixMultiply(matrixA, matrixB, productMatrix, nLength);

    // cout << endl;
    // cout << "Product Matrix " << endl;
    // printMatrix(productMatrix, nLength);

    
    deleteMatrix(matrixB, nLength/2);
    deleteMatrix(matrixC, nLength/2);
    deleteMatrix(matrixD, nLength/2);
    deleteMatrix(matrixE, nLength/2);

    // deleteMatrix(productMatrix, nLength);

    cout << endl;
    system("Pause");
    return 0;
}