#ifndef TP2_TABUSEARCH_H
#define TP2_TABUSEARCH_H


#include "Graph.h"
#include "updatable_priority_queue.h"

class TabuSearch {
private:
    static void reduceDistinctLabelCount(Graph* graph);
    static bool repairGraph(Graph* graph);
    static void incrementConflictCount(better_priority_queue::updatable_priority_queue<int, int*>& conflictPQ, int node);

public:
    static void solve(Graph *graph);
};


#endif //TP2_TABUSEARCH_H
