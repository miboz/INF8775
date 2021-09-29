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

        static double classic(const Matrix &m1,const Matrix &m2, Matrix &result);

        static double recursif(const Matrix &m1,const Matrix &m2, Matrix &result);

        static double recursifAvecLimite(const Matrix &m1,const Matrix &m2, Matrix &result);
};


#endif //INF8775_TP1_ALGORITHM_H
