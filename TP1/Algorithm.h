#ifndef INF8775_TP1_ALGORITHM_H
#define INF8775_TP1_ALGORITHM_H

class Algorithm {

    private:

        static int ***splitMatrix(int **m, const int &halfSize);

        static int **addMatrix(int **a, int **b, int** result, const int &size);

        static int **subtractMatrix(int **a, int **b, int** result, const int &size);

    public:

        static int **classic(int **a, int **b, const int &size);

        static int **strassen(int **a, int **b, const int &size, const int &limit);
};

#endif //INF8775_TP1_ALGORITHM_H
