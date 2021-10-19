//
// Created by milen on 2021-09-15.
//

#ifndef INF8775_TP1_MATRIX_H
#define INF8775_TP1_MATRIX_H
#include <string>

using namespace std;

class Matrix {
    int** data;
    int matrixSize;
public:

    Matrix(int** newData, int size);

    Matrix(int size);

    void deleteMatrix();

    void populateRow(int* &newRow, int index);

    void populateColumn (int* newColumn, int index);

    int getNumber(int i, int j) const;

    void setNumber(const int &i, const int &j, const int &value);

    int** getData();

    int getSize() const;

    bool subdivise(array<Matrix,4>& miniMatrix) const;

    void fuseMatrix (array<Matrix,4>& miniMatrix);

    string toString() const;

    void copyMiniMatrix (Matrix &m, int iMin, int iMax, int jMin, int jMax);

    Matrix operator+(const Matrix &m1);

    Matrix operator-(const Matrix &m1);
};


#endif //INF8775_TP1_MATRIX_H
