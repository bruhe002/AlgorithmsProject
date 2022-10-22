#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "functions.h"

using namespace std;

// Matrix Creation function
int getRandomNumber() {
    srand(time(NULL));
    int randNum =  rand() % 10 + 1;

    return randNum;
}

void printMatrix(int **a, int length) {
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < length; i++) {
            cout << a[i][j] << " ";
        }
    }

    cout << endl;
}

int **createMatrix(int n) {
    int **tempArray2D = new int*[n];

    for (int height = 0; height < n; height++) {
        tempArray2D[height] = new int[n];

        for(int width = 0; width < n; width++) {
            tempArray2D[height][width] = getRandomNumber();
        }
    }

    printMatrix(tempArray2D, n);
    return tempArray2D;
}

void deleteMatrix(int **a, int length) {
    for(int i = 0; i < length; i++) {
        delete [] a[i];
    }

    delete [] a;
}

