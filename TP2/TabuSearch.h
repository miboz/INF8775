#ifndef TP2_TABUSEARCH_H
#define TP2_TABUSEARCH_H


#include "Graph.h"

class TabuSearch {
private:
    static int maxIterationsWithoutImprovement;
    const static int C = 200;
    static const int ALPHA = 2;
    static const int G = 10;

    static int getRandomNumber();
    static int reduceDistinctLabelCount(Graph *graph);
    static bool repairGraph(Graph *graph, int conflictCount);
public:
    static void solve(Graph *graph);
};


#endif //TP2_TABUSEARCH_H
