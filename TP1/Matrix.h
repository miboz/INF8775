//
// Created by milen on 2021-09-15.
//

#ifndef INF8775_TP1_MATRIX_H
#define INF8775_TP1_MATRIX_H
#include <vector>

using namespace std;

class Matrix {
    vector<vector<int>> data;
public:

    Matrix(vector<vector<int>> newData);

    Matrix();

    void populateRow(vector<int> newRow);

    void populateColumn (vector<int> newColumn);

    int getNumber(int i, int j);

    int getSize();

    bool subdivise(array<Matrix,4>& miniMatrix);
};


#endif //INF8775_TP1_MATRIX_H
