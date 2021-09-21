#include <iostream>
#include <fstream>
#include <string>
#include "Matrix.h"

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
    vector<vector<int>> matrixData(size);

    for (int i = 0; i < size; ++i) {
        getline(fileStream, line);
        vector<int> matrixLine(size);
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
    Matrix matrix1 = getMatrixFromFileName(argv[1]);
    Matrix matrix2 = getMatrixFromFileName(argv[2]);
    return 0;
}
