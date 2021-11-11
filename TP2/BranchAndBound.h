#ifndef TP2_BRANCHANDBOUND_H
#define TP2_BRANCHANDBOUND_H


#include "Graph.h"
#include <stack>
#include "updatable_priority_queue.h"

class BranchAndBound {
private:
    struct StackElement {
        int level;
        int newLabel;
        int currentCost;
    };

    static void addNextStates(std::stack<StackElement> &stackNodesToProcess,
                       better_priority_queue::updatable_priority_queue<int, Node *> &pQ,
                       StackElement &stackElement);
    static void travelDown(std::stack<Node*> &stackNodesToProcess,
                       better_priority_queue::updatable_priority_queue<int, Node *> &pQ,
                       StackElement &stackElement);
    static void travelUp(std::stack<Node*> &stackNodesToProcess,
                       better_priority_queue::updatable_priority_queue<int, Node *> &pQ,
                       StackElement &stackElement,
                       int& level);
public:
    static void solve(Graph *graph);
};


#endif //TP2_BRANCHANDBOUND_H
