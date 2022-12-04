#include <iostream>
#include <iomanip>
#include <time.h>
#include <vector>
#include <chrono>

#include "functions.h"

using namespace std;
using namespace std::chrono;

int main() {
    
    cout << fixed << setprecision(30) << endl;

    // // Matrix creation tests
    // Needed for random number generator
    srand(time(NULL));
    int nLength = 0;
    cout << "Please enter a positive number: ";
    cin >> nLength;
    cout << endl;

    vector<vector<int>> vect1(nLength, vector<int> (nLength, 0));
    vector<vector<int>> vect2(nLength, vector<int> (nLength, 0));
    
    createMatrix(vect1, nLength);
    createMatrix(vect2, nLength);
    
    // Instance Test
    // vector<vector<int>> vect1 = {{2, 0, -1, 6},
    //                              {3, 7, 8, 0},
    //                              {-5, 1, 6, -2},
    //                              {8, 0, 1, 7}};

    // vector<vector<int>> vect2 = {{0, 1, 6, 3},
    //                              {-2, 8, 7, 1},
    //                              {2, 0, -1, 0},
    //                              {9, 1, 6, -2}};
    // int nLength = vect1.size();                             


    printMatrix(vect1, nLength);
    cout << endl;
    printMatrix(vect2, nLength);
    cout << endl;

    clock_t testOneStart = clock();
    vector<vector<int>> product1 = matrixMultiply(vect1, vect2, nLength);
    clock_t testOneEnd = clock();
    double testOneDuration = (double(double(testOneEnd) - double(testOneStart)) / double(CLOCKS_PER_SEC));
    printMatrix(product1, nLength);
    cout << endl;
    cout << "Brute Force Took " << testOneDuration << " sec" << endl << endl;

    // time_t testTwoStart, testTwoEnd;
    clock_t testTwoStart = clock();
    cout << "Enter test 2" << endl;
    vector<vector<int>> product2 = matrixMultiplyDC(vect1, vect2, nLength);
    clock_t testTwoEnd = clock();
    double testTwoDuration = (double(testTwoEnd - testTwoStart) / double(CLOCKS_PER_SEC));
    printMatrix(product2, nLength);
    cout << endl;
    cout << "Naive Divide and Conquer Took " << testTwoDuration << " sec" << endl << endl;
    
    // time_t testThreeStart, testThreeEnd;
    vector<vector<int>> product3(nLength, vector<int>(nLength, 0));
    clock_t testThreeStart = clock();
    matrixMultiplyStraussen(vect1, vect2, product3, nLength);
    clock_t testThreeEnd = clock();
    double testThreeDuration = (double(testThreeEnd - testThreeStart) / double(CLOCKS_PER_SEC));
    printMatrix(product3, nLength);
    cout << endl;
    cout << "Straussen's Algorithm Took " << testThreeDuration << " sec" << endl << endl;

    cout << endl;
    system("Pause");
    return 0;
}
