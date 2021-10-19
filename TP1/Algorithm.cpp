//
// Created by milen on 2021-09-29.
//

#include "Algorithm.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <array>
#include "chrono"

Algorithm::Algorithm(){}

Matrix Algorithm::classic(const Matrix &a, const Matrix &b){
    int size = a.getSize();
    Matrix result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int total = 0;
            for (int k = 0; k < size; ++k) {
                total += a.getNumber(i, k) * b.getNumber(k, j);
            }
            result.setNumber(i, j, total);
        }
    }
    return result;
}

Matrix Algorithm::recursif(const Matrix &a, const Matrix &b){

    int size = a.getSize();

    if (size == 1) {
        Matrix c(1);
        c.setNumber(0,0,(a.getNumber(0,0) * b.getNumber(0,0)));
        return c;
    }
    array<Matrix,4> miniMatrixA = {Matrix(size/2), Matrix(size/2), Matrix(size/2), Matrix(size/2)};
    a.subdivise(miniMatrixA);
    array<Matrix,4> miniMatrixB = {Matrix(size/2), Matrix(size/2), Matrix(size/2), Matrix(size/2)};
    b.subdivise(miniMatrixB);

    Matrix m1 = recursif(miniMatrixA[0] + miniMatrixA[3], miniMatrixB[0] + miniMatrixB[3]);
    Matrix m2 = recursif(miniMatrixA[2] + miniMatrixA[3], miniMatrixB[0]);
    Matrix m3 = recursif(miniMatrixA[0], miniMatrixB[1] - miniMatrixB[3]);
    Matrix m4 = recursif(miniMatrixA[3], miniMatrixB[2] - miniMatrixB[0]);
    Matrix m5 = recursif(miniMatrixA[0] + miniMatrixA[1], miniMatrixB[3]);
    Matrix m6 = recursif(miniMatrixA[2] - miniMatrixA[0], miniMatrixB[0] + miniMatrixB[1]);
    Matrix m7 = recursif(miniMatrixA[1] - miniMatrixA[3], miniMatrixB[2] + miniMatrixB[3]);

    array<Matrix, 4> miniMatrixC = {m1 + m4 - m5 + m7, m3 + m5, m2 + m4, m1 - m2 + m3 + m6};

    Matrix result = Matrix(size);
    result.fuseMatrix(miniMatrixC);

    miniMatrixA[0].deleteMatrix();
    miniMatrixA[1].deleteMatrix();
    miniMatrixA[2].deleteMatrix();
    miniMatrixA[3].deleteMatrix();

    miniMatrixB[0].deleteMatrix();
    miniMatrixB[1].deleteMatrix();
    miniMatrixB[2].deleteMatrix();
    miniMatrixB[3].deleteMatrix();

    miniMatrixC[0].deleteMatrix();
    miniMatrixC[1].deleteMatrix();
    miniMatrixC[2].deleteMatrix();
    miniMatrixC[3].deleteMatrix();

    m1.deleteMatrix();
    m2.deleteMatrix();
    m3.deleteMatrix();
    m4.deleteMatrix();
    m5.deleteMatrix();
    m6.deleteMatrix();
    m7.deleteMatrix();

    return result;
}

Matrix Algorithm::recursifAvecLimite(const Matrix &a, const Matrix &b,const int limite){
    int size = a.getSize();

    if (size <= limite) {
        return classic(a, b);
    }



    array<Matrix,4> miniMatrixA = {Matrix(size/2), Matrix(size/2), Matrix(size/2), Matrix(size/2)};
    a.subdivise(miniMatrixA);
    array<Matrix,4> miniMatrixB = {Matrix(size/2), Matrix(size/2), Matrix(size/2), Matrix(size/2)};
    b.subdivise(miniMatrixB);

    Matrix m1 = recursifAvecLimite(miniMatrixA[0] + miniMatrixA[3], miniMatrixB[0] + miniMatrixB[3], limite);
    Matrix m2 = recursifAvecLimite(miniMatrixA[2] + miniMatrixA[3], miniMatrixB[0], limite);
    Matrix m3 = recursifAvecLimite(miniMatrixA[0], miniMatrixB[1] - miniMatrixB[3], limite);
    Matrix m4 = recursifAvecLimite(miniMatrixA[3], miniMatrixB[2] - miniMatrixB[0], limite);
    Matrix m5 = recursifAvecLimite(miniMatrixA[0] + miniMatrixA[1], miniMatrixB[3], limite);
    Matrix m6 = recursifAvecLimite(miniMatrixA[2] - miniMatrixA[0], miniMatrixB[0] + miniMatrixB[1], limite);
    Matrix m7 = recursifAvecLimite(miniMatrixA[1] - miniMatrixA[3], miniMatrixB[2] + miniMatrixB[3], limite);

    array<Matrix, 4> miniMatrixC = {m1 + m4 - m5 + m7, m3 + m5, m2 + m4, m1 - m2 + m3 + m6};


    Matrix result = Matrix(size);
    result.fuseMatrix(miniMatrixC);

    miniMatrixA[0].deleteMatrix();
    miniMatrixA[1].deleteMatrix();
    miniMatrixA[2].deleteMatrix();
    miniMatrixA[3].deleteMatrix();

    miniMatrixB[0].deleteMatrix();
    miniMatrixB[1].deleteMatrix();
    miniMatrixB[2].deleteMatrix();
    miniMatrixB[3].deleteMatrix();

    miniMatrixC[0].deleteMatrix();
    miniMatrixC[1].deleteMatrix();
    miniMatrixC[2].deleteMatrix();
    miniMatrixC[3].deleteMatrix();

    m1.deleteMatrix();
    m2.deleteMatrix();
    m3.deleteMatrix();
    m4.deleteMatrix();
    m5.deleteMatrix();
    m6.deleteMatrix();
    m7.deleteMatrix();

    return result;
}