#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Matrix.h"
#include "Algorithm.h"
#include "chrono"

using namespace std;

//From https://slaystudy.com/c-split-string-by-space-into-vector/
void splitString(const string& s, vector<int> &v){

    string temp;
    for(char i : s) {
        if(i == ' ') {
            v.push_back(stoi(temp));
            temp = "";
        }
        else {
            temp.push_back(i);
        }
    }
    v.push_back(stoi(temp));
}

Matrix getMatrixFromFileName(const string& fileName) {
    ifstream fileStream(fileName);
    string line;
    getline(fileStream, line);
    int size = (int)pow(2, stoi(line));
    vector<vector<int>> matrixData;

    for (int i = 0; i < size; ++i) {
        getline(fileStream, line);
        vector<int> matrixLine;
        splitString(line, matrixLine);
        matrixData.push_back(matrixLine);
    }
    fileStream.close();

    return {matrixData};
}

Matrix getResult(const Matrix &matrix1, const Matrix &matrix2, const string &algorithmType) {
    if (algorithmType == "conv") {
        return Algorithm::classic(matrix1, matrix2);
    }
    if (algorithmType == "strassen") {
        return Algorithm::recursif(matrix1, matrix2);
    }
    return Algorithm::recursifAvecLimite(matrix1, matrix2, 4);
}

int main(int argc, char** argv) {
    if (argc != 5) {
        cerr << "Must give 4 arguments";
        return 1;
    }
    // TODO se rappeler de faire ca avec ;es argv[1] et argv[2]
    string folder = "ex/s2-t5-n5-r1/";
    string pathM1 = argv[1];
    string pathM2 = argv[2];
    string algorithmType = argv[3];
    string printParams = argv[4];
    Matrix matrix1 = getMatrixFromFileName(pathM1);
    Matrix matrix2 = getMatrixFromFileName(pathM2);
    auto start = chrono::steady_clock::now();

    Matrix result = getResult(matrix1, matrix2, algorithmType);

    auto end = chrono::steady_clock::now();
    auto diff = end - start;

    if (printParams.find('p') != std::string::npos) {
        cout << result.toString();
    }
    if (printParams.find('t') != std::string::npos) {
        cout <<  chrono::duration <double, milli> (diff).count();
    }
    return 0;
}
