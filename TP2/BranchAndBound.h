#ifndef TP2_BRANCHANDBOUND_H
#define TP2_BRANCHANDBOUND_H


#include "Graph.h"

class BranchAndBound {
private:
    struct StackElement {
        int level;
        int newLabel;
        int currentCost;
    };
public:
    static void solve(Graph *graph);
};


#endif //TP2_BRANCHANDBOUND_H
