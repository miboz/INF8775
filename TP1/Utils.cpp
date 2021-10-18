#ifndef INF8775_TP1_UTILS_CPP
#define INF8775_TP1_UTILS_CPP

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//From https://slaystudy.com/c-split-string-by-space-into-vector/
static void splitString(const string &s, int *v){
    string temp;
    int i = 0;
    for(char c : s) {
        if(c == ' ') {
            v[i] = stoi(temp);
            temp = "";
            i += 1;
        }
        else {
            temp.push_back(c);
        }
    }
    v[i] = stoi(temp);
}

static int **generateMatrix(const int &size) {
    int **matrixData = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrixData[i] = new int[size];
    }
    return matrixData;
}

static void deleteMatrix(int **m, const int &size) {
    for (int i = 0; i < size; ++i) {
        delete[] m[i];
    }
    delete[] m;
}

static int **getMatrixFromFile(const string& fileName, int &size) {
    ifstream fileStream(fileName);
    string line;
    getline(fileStream, line);
    size = (int)pow(2, stoi(line));
    int **matrixData = generateMatrix(size);

    for (int i = 0; i < size; ++i) {
        getline(fileStream, line);
        splitString(line, matrixData[i]);
    }
    fileStream.close();

    return matrixData;
}

static void printMatrix(int **matrix, const int &size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout <<  matrix[i][size - 1] << endl;
    }
}

#endif //INF8775_TP1_UTILS_CPP