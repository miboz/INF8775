//
// Created by milen on 2021-09-15.
//

#include <string>
#include "Matrix.h"
#include <array>
#include <sstream>

Matrix::Matrix(vector<vector<int>> newData){

    data = newData;
}

Matrix::Matrix(int size) {

    for (int i = 0; i < size; ++i) {
        vector<int> matrixLine(size);
        data.push_back(matrixLine);
    }
}

void Matrix::populateRow (const vector<int> &newRow, int index) {
    data[index] = newRow;
}

void Matrix::populateColumn (vector<int> newColumn) {

    if (data.size() == newColumn.size()) {
        for (int i=0;i<data.size();i++) {
            data[i].push_back(newColumn[i]);
        }
    }
}

int Matrix::getNumber(int i, int j) const {
    return data[i][j];
}

void Matrix::setNumber(const int &i, const int &j, const int &value) {
    data[i][j] = value;
}

int Matrix::getSize() const {
    return data.size();
}


bool Matrix::subdivise(array<Matrix,4>& miniMatrix) const {
    if(data.size() % 2 != 0) {
        return false;
    }
    int halfsize = data.size()/2;
    for (int i=0;i<data.size();i++) {
        if(i<halfsize){
            miniMatrix[0].populateRow(vector<int> (data[i].begin(), data[i].begin() + halfsize), i);
            miniMatrix[1].populateRow(vector<int> (data[i].begin() + halfsize, data[i].end()), i);
        } else {
            miniMatrix[2].populateRow(vector<int> (data[i].begin(), data[i].begin() + halfsize), i - halfsize);
            miniMatrix[3].populateRow(vector<int> (data[i].begin() + halfsize, data[i].end()), i - halfsize);
        }
    }

    return true;
}

string Matrix::toString() const {
    std::stringstream ss;
    for (auto & line : data)
    {
        ss << line[0];
        for (int j = 1; j < line.size(); j++)
        {
            ss << " " << line[j];
        }
        ss << endl;
    }
    return ss.str();
}

Matrix Matrix::operator+(const Matrix &m1) {
    Matrix matrixTemp = Matrix(this->getSize());
    for (int i=0; i < data.size(); i++) {
        for (int j=0; j < data[i].size(); j++) {
            matrixTemp.setNumber(i, j, this->getNumber(i, j) + m1.getNumber(i, j));
        }
    }
    return matrixTemp;
}

Matrix Matrix::operator-(const Matrix &m1) {
    Matrix matrixTemp(this->getSize());
    for (int i=0; i < data.size(); i++) {
        for (int j=0; j < data[i].size(); j++) {
            matrixTemp.setNumber(i, j, getNumber(i, j) - m1.getNumber(i, j));
        }
    }
    return matrixTemp;
}

void Matrix::fuseMatrix (array<Matrix,4>& miniMatrix) {
    int size = data.size();
    int halfsize = size/2;

    copyMiniMatrix(miniMatrix[0], 0, halfsize, 0, halfsize);
    copyMiniMatrix(miniMatrix[1], 0, halfsize, halfsize, size);
    copyMiniMatrix(miniMatrix[2], halfsize, size, 0, halfsize);
    copyMiniMatrix(miniMatrix[3], halfsize, size, halfsize, size);

}

void Matrix::copyMiniMatrix (Matrix &m, int iMin, int iMax, int jMin, int jMax) {
    for (int i=iMin; i < iMax; i++) {
        for (int j=jMin; j < jMax; j++) {
            setNumber(i, j, m.getNumber(i - iMin, j - jMin));
        }
    }
}