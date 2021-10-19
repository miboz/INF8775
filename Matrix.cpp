//
// Created by milen on 2021-09-15.
//

#include <string>
#include "Matrix.h"
#include <array>
#include <sstream>

Matrix::Matrix(int** newData, int size){
    matrixSize = size;

    data = newData;
}

Matrix::Matrix(int size) {
    matrixSize = size;
    data = new int*[size];

    for (int i = 0; i < size; ++i) {
        data[i] = new int[size];
    }
}

void Matrix::populateRow (int* &newRow, int index) {
    data[index] = newRow;
}

void Matrix::populateColumn (int* newColumn, int index) {

        for (int i=0;i<matrixSize;i++) {
            data[i][index] = newColumn[i];
        }
}

int Matrix::getNumber(int i, int j) const {
    return data[i][j];
}

void Matrix::setNumber(const int &i, const int &j, const int &value) {
    data[i][j] = value;
}

int Matrix::getSize() const {
    return matrixSize;
}


bool Matrix::subdivise(array<Matrix,4>& miniMatrix) const {
    if(matrixSize % 2 != 0) {
        return false;
    }
    int halfsize = matrixSize/2;
    for(int i=0; i<halfsize; i++) {
        for(int j=0; j<halfsize; j++) {
            miniMatrix[0].setNumber(i,j,data[i][j]);
            miniMatrix[1].setNumber(i,j, data[i][halfsize + j]);
            miniMatrix[2].setNumber(i,j, data[halfsize + i][j]);
            miniMatrix[3].setNumber(i,j, data[halfsize + i][halfsize + j]);
        }
    }
            return true;
}

string Matrix::toString() const {
    std::stringstream ss;
    for(int i=0; i < matrixSize; i++)
    {
        ss << data[i][0];
        for (int j = 1; j < matrixSize; j++)
        {
            ss << " " << data[i][j];
        }
        ss << endl;
    }
    return ss.str();
}

Matrix Matrix::operator+(const Matrix &m1) {
    Matrix matrixTemp = Matrix(this->getSize());
    for (int i=0; i < matrixSize; i++) {
        for (int j=0; j < matrixSize; j++) {
            matrixTemp.setNumber(i, j, this->getNumber(i, j) + m1.getNumber(i, j));
        }
    }
    return matrixTemp;
}

Matrix Matrix::operator-(const Matrix &m1) {
    Matrix matrixTemp(this->getSize());
    for (int i=0; i < matrixSize; i++) {
        for (int j=0; j < matrixSize; j++) {
            matrixTemp.setNumber(i, j, getNumber(i, j) - m1.getNumber(i, j));
        }
    }
    return matrixTemp;
}

void Matrix::fuseMatrix (array<Matrix,4>& miniMatrix) {
    int size = matrixSize;
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

void Matrix::deleteMatrix() {
    for (int i = 0; i < matrixSize; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

int** Matrix::getData() {
    return data;
}