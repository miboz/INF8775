//
// Created by milen on 2021-09-29.
//

#ifndef INF8775_TP1_ALGORITHM_H
#define INF8775_TP1_ALGORITHM_H


#include "Matrix.h"

class Algorithm {

    private:

        Algorithm();

    public:

        static Matrix classic(const Matrix &a, const Matrix &b);

        static Matrix recursif(const Matrix &a, const Matrix &b);

        static Matrix recursifAvecLimite(const Matrix &a, const Matrix &b,const int limite);
};


#endif //INF8775_TP1_ALGORITHM_H
