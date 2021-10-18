#include <iostream>
#include <string>
#include "chrono"
#include "Utils.cpp"
#include "Algorithm.h"

using namespace std;

int** getResult(int** a, int** b, const string &algorithmType, const int &size) {
    if (algorithmType == "conv") {
        return Algorithm::classic(a, b, size);
    }
    if (algorithmType == "strassen") {
        return Algorithm::strassen(a, b, size, 1);
    }
    return Algorithm::strassen(a, b, size, 64);
}

int main(int argc, char** argv) {
    if (argc != 5) {
        cerr << "Must give 4 arguments";
        return 1;
    }
    string pathM1 = argv[1];
    string pathM2 = argv[2];
    string algorithmType = argv[3];
    string printParams = argv[4];
    int size;
    int **a = getMatrixFromFile(pathM1, size);
    int **b = getMatrixFromFile(pathM2, size);
    auto start = chrono::steady_clock::now();

    int **result = getResult(a, b, algorithmType, size);

    auto end = chrono::steady_clock::now();
    auto diff = end - start;

    if (printParams.find('p') != std::string::npos) {
        printMatrix(result, size);
    }
    if (printParams.find('t') != std::string::npos) {
        cout <<  chrono::duration <double, milli> (diff).count();
    }
    deleteMatrix(a, size);
    deleteMatrix(b, size);
    deleteMatrix(result, size);
    return 0;
}
