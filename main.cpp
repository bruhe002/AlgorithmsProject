#include <iostream>

#include "functions.h"

using namespace std;

int main() {
    // Matrix creation tests
    int nLength = 0;
    cout << "Please enter a positive number: ";
    cin >> nLength;
    cout << endl;
    
    int **testMatrix = createMatrix(nLength);

    deleteMatrix(testMatrix, nLength);

    cout << endl;
    system("Pause");
    return 0;
}