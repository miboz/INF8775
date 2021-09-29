//
// Created by milen on 2021-09-29.
//

#include "Algorithm.h"
#include <ctime>
#include <iostream>
#include <iomanip>

Algorithm::Algorithm(){}

double Algorithm::classic(const Matrix &m1,const Matrix &m2, Matrix &result){
    clock_t clock_start = clock();
    int size = m1.getSize();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int total = 0;
            for (int k = 0; k < size; ++k) {
                total += m1.getNumber(i, k) * m2.getNumber(k, j);
            }
            result.setNumber(i, j, total);
        }
    }

    clock_t clock_end = clock();
    // TODO regarder ca plus tard c'est un peu sus
    return 1000.0 * (clock_end-clock_start) / CLOCKS_PER_SEC; // rappel: milliseconds
}

double Algorithm::recursif(const Matrix &m1,const Matrix &m2, Matrix &result){
    clock_t clock_start = clock();



    clock_t clock_end = clock();
    return 1000.0 * (clock_end-clock_start) / CLOCKS_PER_SEC;// rappel: milliseconds
}

double Algorithm::recursifAvecLimite(const Matrix &m1,const Matrix &m2, Matrix &result){
    clock_t clock_start = clock();




    clock_t clock_end = clock();
    return 1000.0 * (clock_end-clock_start) / CLOCKS_PER_SEC;// rappel: milliseconds
}
