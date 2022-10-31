#include <iostream>
#include <iomanip>
#include <time.h>
#include <vector>
#include <chrono>

#include "functions.h"

using namespace std;
using namespace std::chrono;

double measureTime(clock_t start, clock_t end);

int main() {
    // Needed for random number generator
    
    srand(time(NULL));
    cout << fixed << setprecision(20) << endl;
    // Matrix creation tests
    int nLength = 0;
    cout << "Please enter a positive number: ";
    cin >> nLength;
    cout << endl;

    vector<vector<int>> vect1(nLength, vector<int> (nLength, 0));
    vector<vector<int>> vect2(nLength, vector<int> (nLength, 0));
    
    createMatrix(vect1, nLength);
    createMatrix(vect2, nLength);

    // printMatrix(vect1, nLength);
    // cout << endl;
    // printMatrix(vect2, nLength);
    // cout << endl;
    clock_t testOneStart = clock();
    
    vector<vector<int>> product1 = matrixMultiply(vect1, vect2, nLength);
    clock_t testOneEnd = clock();
    double testOneDuration = double(testOneEnd - testOneStart) / double(CLOCKS_PER_SEC);
    // printMatrix(product1, nLength);
    cout << endl;
    cout << testOneDuration << " mms" << endl << endl;

    time_t testTwoStart, testTwoEnd;
    time(&testTwoStart);
    vector<vector<int>> product2 = matrixMultiplyDC(vect1, vect2);
    time(&testTwoEnd);
    double testTwoDuration = double(testTwoEnd - testTwoStart);
    // printMatrix(product2, nLength);
    cout << endl;
    cout << testTwoDuration << " mms" << endl << endl;
    
    
    
    // int **matrixB = partitionMatrix(matrixA, 0, nLength/2 - 1, 0, nLength/2 - 1);
    // int **matrixC = partitionMatrix(matrixA, nLength/2, nLength - 1, 0, nLength/2 - 1);
    // int **matrixD = partitionMatrix(matrixA, 0, nLength/2 - 1, nLength/2, nLength - 1);
    // // cout << "Bout to begin" << endl;
    // int **matrixE = partitionMatrix(matrixA, nLength/2, nLength - 1, nLength/2, nLength - 1);
    // // int **productMatrix = createEmptyMatrix(nLength);
    
    // cout << endl;
    // cout << "Matrix 1: " << endl;
    // printMatrix(matrixA, nLength);


    // cout << endl;
    // cout << "Matrix 2: " << endl;
    // printMatrix(matrixB, nLength);
    // try {
    //     //Begin timer
    //     auto testOneStart = high_resolution_clock::now();
    //     int **testResult1 = matrixMultiply(matrixA, matrixB, nLength);
    //     auto testOneEnd = high_resolution_clock::now();
    //     auto testOneDuration = duration_cast<microseconds>(testOneEnd - testOneStart);

    //     cout << endl;
    //     cout << "Test Result 1 Runtime: " << testOneDuration.count() << endl;
    //     deleteMatrix(testResult1, nLength);
    // // printMatrix(testResult1, nLength);
    // } catch(const exception& ex) {
    //     cerr << ex.what() << endl << "Error caught in Test 2" << endl;
    // }    

    // try {
    //     auto testTwoStart = high_resolution_clock::now();
    //     int **testResult2 = matrixMultiplyDC(matrixA, matrixB, nLength);
    //     auto testTwoEnd = high_resolution_clock::now();
    //     auto testTwoDuration = duration_cast<microseconds>(testTwoEnd - testTwoStart);
        

    //     cout << endl;
    //     cout << "Test Result 2 Runtime: " << testTwoDuration.count() << endl;
    //     // printMatrix(testResult2, nLength);
    //     deleteMatrix(testResult2, nLength);
    // } catch(const exception& ex) {
    //     cerr << ex.what() << endl << "Error caught in Test 2" << endl;
    // }
    
    // try{
    //     auto testThreeStart = high_resolution_clock::now();
    //     int **testResult3 = matrixMultiplyStraussen(matrixA, matrixB, nLength);
    //     auto testThreeEnd = high_resolution_clock::now();
    //     auto testThreeDuration = duration_cast<microseconds>(testThreeEnd - testThreeStart);

    //     cout << endl;
    //     cout << "Test Result 3 runtime: " << testThreeDuration.count() << endl;
    //     // printMatrix(testResult3, nLength);
    //     deleteMatrix(testResult3, nLength);
    // }
    // catch(const exception& ex) {
    //     cerr << ex.what() << endl << "Error caught in Test 2" << endl;
    // }
    
    // cout << endl;
    // cout << "Multiplying Matrices..." << endl;
    // matrixMultiply(matrixA, matrixB, productMatrix, nLength);

    // cout << endl;
    // cout << "Product Matrix " << endl;
    // printMatrix(productMatrix, nLength);

    // deleteMatrix(matrixA, nLength);   
    // deleteMatrix(matrixB, nLength);

    // deleteMatrix(productMatrix, nLength);

    cout << endl;
    system("Pause");
    return 0;
}


double measureTime(clock_t start, clock_t end){
    return ((end - start) / CLOCKS_PER_SEC) * 1000000.0;
}