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
    int **productMatrix = createEmptyMatrix(nLength);
    
    cout << endl;
    cout << "Matrix 1: " << endl;
    printMatrix(matrixA, nLength);
    
    cout << endl;
    cout << "Matrix 2: " << endl;
    printMatrix(matrixB, nLength);
    
    cout << endl;
    cout << "Multiplying Matrices..." << endl;
    matrixMultiply(matrixA, matrixB, productMatrix, nLength);

    cout << endl;
    cout << "Product Matrix " << endl;
    printMatrix(productMatrix, nLength);

    deleteMatrix(matrixA, nLength);
    deleteMatrix(matrixB, nLength);
    deleteMatrix(productMatrix, nLength);

    cout << endl;
    system("Pause");
    return 0;
}