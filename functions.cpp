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
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < length; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

}

int **createMatrix(int n) {
    srand(time(NULL));
    int **tempArray2D = new int*[n];

    for (int height = 0; height < n; height++) {
        tempArray2D[height] = new int[n];

        for(int width = 0; width < n; width++) {
            tempArray2D[height][width] = getRandomNumber();
        }
    }

    return tempArray2D;
}

void deleteMatrix(int **a, int length) {
    for(int i = 0; i < length; i++) {
        delete [] a[i];
    }

    delete [] a;
}

