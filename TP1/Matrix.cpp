//
// Created by milen on 2021-09-15.
//

#include <string>
#include "Matrix.h"
#include <array>

Matrix::Matrix(vector<vector<int>> newData){

data = newData;

}

void Matrix::populateRow (vector<int> newRow) {
    data.push_back(newRow);
}

void Matrix::populateColumn (vector<int> newColumn) {

    if (data.size() == newColumn.size()) {
        for (int i=0;i<data.size();i++) {
            data[i].push_back(newColumn[i]);
        }
    }
}

int Matrix::getNumber(int i, int j) {
    return data[i][j];

}

int Matrix::getSize() {
    return data.size();
}


bool Matrix::subdivise(array<Matrix,4>& miniMatrix) {
    if(data.size() % 2 != 0) {
        return false;
    }
    int halfsize = data.size()/2;
    for (int i=0;i<data.size();i++) {
      if(i<halfsize){
          miniMatrix[0].populateRow(vector<int> (data[i].begin(), data[i].begin() + (halfsize-1)));
          miniMatrix[1].populateRow(vector<int> (data[i].begin() + halfsize, data[i].end()));
      } else {
          miniMatrix[2].populateRow(vector<int> (data[i].begin(), data[i].begin() + (halfsize-1)));
          miniMatrix[3].populateRow(vector<int> (data[i].begin() + halfsize, data[i].end()));
      }
    }

    return true;


}