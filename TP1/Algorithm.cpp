#include "Algorithm.h"
#include <array>
#include "Utils.cpp"

int **Algorithm::classic(int **a, int **b, const int &size){
    int **result = generateMatrix(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

int **Algorithm::strassen(int **a, int **b, const int &size, const int &limit) {

    if (size <= limit) {
        return classic(a, b, size);
    }
    const int halfSize = size / 2;
    int ***miniMatrixA = splitMatrix(a, halfSize);
    int ***miniMatrixB = splitMatrix(b, halfSize);

    int **m11 = addMatrix(miniMatrixA[0], miniMatrixA[3], generateMatrix(halfSize), halfSize);
    int **m12 = addMatrix(miniMatrixB[0], miniMatrixB[3], generateMatrix(halfSize), halfSize);
    int **m21 = addMatrix(miniMatrixA[2], miniMatrixA[3], generateMatrix(halfSize), halfSize);
    int **m32 = subtractMatrix(miniMatrixB[1], miniMatrixB[3], generateMatrix(halfSize), halfSize);
    int **m42 = subtractMatrix(miniMatrixB[2], miniMatrixB[0], generateMatrix(halfSize), halfSize);
    int **m51 = addMatrix(miniMatrixA[0], miniMatrixA[1], generateMatrix(halfSize), halfSize);
    int **m61 = subtractMatrix(miniMatrixA[2], miniMatrixA[0], generateMatrix(halfSize), halfSize);
    int **m62 = addMatrix(miniMatrixB[0], miniMatrixB[1], generateMatrix(halfSize), halfSize);
    int **m71 = subtractMatrix(miniMatrixA[1], miniMatrixA[3], generateMatrix(halfSize), halfSize);
    int **m72 = addMatrix(miniMatrixB[2], miniMatrixB[3], generateMatrix(halfSize), halfSize);


    int **m1 = strassen(m11, m12, halfSize, limit);
    int **m2 = strassen(m21, miniMatrixB[0], halfSize, limit);
    int **m3 = strassen(miniMatrixA[0], m32, halfSize, limit);
    int **m4 = strassen(miniMatrixA[3], m42, halfSize, limit);
    int **m5 = strassen(m51, miniMatrixB[3], halfSize, limit);
    int **m6 = strassen(m61, m62, halfSize, limit);
    int **m7 = strassen(m71, m72, halfSize, limit);

    deleteMatrix(m11, halfSize);
    deleteMatrix(m12, halfSize);
    deleteMatrix(m21, halfSize);
    deleteMatrix(m32, halfSize);
    deleteMatrix(m42, halfSize);
    deleteMatrix(m51, halfSize);
    deleteMatrix(m61, halfSize);
    deleteMatrix(m62, halfSize);
    deleteMatrix(m71, halfSize);
    deleteMatrix(m72, halfSize);

    delete[] miniMatrixA;
    delete[] miniMatrixB;

    int **result = generateMatrix(size);
    int **c12 = new int*[halfSize];
    int **c22 = new int*[halfSize];
    for (int i = 0; i < halfSize; ++i) {
        c12[i] = result[i] + halfSize;
        c22[i] = result[i + halfSize] + halfSize;
    }
    // m1 + m4 - m5 + m7
    // m3 + m5
    // m2 + m4
    // m1 - m2 + m3 + m6
    int** op1 = addMatrix(m1, m4, generateMatrix(halfSize), halfSize); // m1 + m4
    int** op2 = subtractMatrix(op1, m5, generateMatrix(halfSize), halfSize); // (m1 + m4) - m5
    addMatrix(op2, m7, result, halfSize); // (m1 + m4 - m5) + m7

    addMatrix(m3, m5, c12, halfSize); // m3 + m5

    addMatrix(m2, m4, result + halfSize, halfSize); // m3 + m5

    int** op3 = subtractMatrix(m1, m2, generateMatrix(halfSize), halfSize); // m1 - m2
    int** op4 = addMatrix(op3, m3, generateMatrix(halfSize), halfSize); // (m1 - m2) + m3
    addMatrix(op4, m6, c22, halfSize); // (m1 - m2 + m3) + m6

    deleteMatrix(op1, halfSize);
    deleteMatrix(op2, halfSize);
    deleteMatrix(op3, halfSize);
    deleteMatrix(op4, halfSize);
    deleteMatrix(m1, halfSize);
    deleteMatrix(m2, halfSize);
    deleteMatrix(m3, halfSize);
    deleteMatrix(m4, halfSize);
    deleteMatrix(m5, halfSize);
    deleteMatrix(m6, halfSize);
    deleteMatrix(m7, halfSize);

    return result;
}

int ***Algorithm::splitMatrix(int **m, const int &halfSize) {

    int ***result = new int**[4];
    result[0] = m;
    result[1] = new int*[halfSize];
    result[2] = m + halfSize;
    result[3] = new int*[halfSize];
    for (int i = 0; i < halfSize; ++i) {
        result[1][i] = m[i] + halfSize;
        result[3][i] = m[i + halfSize] + halfSize;
    }
    return result;
}

int **Algorithm::addMatrix(int **a, int **b, int** result, const int &size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    return result;
}

int **Algorithm::subtractMatrix(int **a, int **b, int** result, const int &size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
    return result;
}
