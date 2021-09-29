#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Matrix.h"
#include "Algorithm.h"

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

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Must give 2 arguments";
        return 1;
    }
    // TODO se rappeler de faire ca avec ;es argv[1] et argv[2]
    string folder = "ex/s6-t1-n2-r1/";
    string pathM1 = folder + "ex6_0";
    string pathM2 = folder + "ex6_1";
    Matrix matrix1 = getMatrixFromFileName(pathM1);
    Matrix matrix2 = getMatrixFromFileName(pathM2);
//    cout << matrix1.toString();
//    cout << matrix2.toString();
    Matrix result = Matrix(matrix1.getSize());
    double time = Algorithm::classic(matrix1, matrix2, result);
    double a = 64123.1;
//    cout << result.toString();
    cout << std::fixed << setprecision(2);
    cout << time << endl;
    return 0;
}
