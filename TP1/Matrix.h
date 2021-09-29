//
// Created by milen on 2021-09-15.
//

#ifndef INF8775_TP1_MATRIX_H
#define INF8775_TP1_MATRIX_H
#include <vector>
#include <string>

using namespace std;

class Matrix {
    vector<vector<int>> data;
public:

    Matrix(vector<vector<int>> newData);

    Matrix(int size);

    void populateRow(const vector<int> &newRow);

    void populateColumn (vector<int> newColumn);

    int getNumber(int i, int j) const;

    void setNumber(const int &i, const int &j, const int &value);

    int getSize() const;

    bool subdivise(array<Matrix,4>& miniMatrix) const;

    string toString() const;
};


#endif //INF8775_TP1_MATRIX_H
