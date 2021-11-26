#ifndef TP3_SOLUTION_H
#define TP3_SOLUTION_H

#include <set>
#include "Graph.h"
#include "List.h"

class Solution {
public:
    static void solve(Graph *g);
    static List* posaHeuristic(Graph *g);
    static bool tryExtendPath(List *path, bool isTail);
    static bool posaSearch(List *path, std::set<Node*> &visitedEndpoints);
    static int getScore(List *path);
    static bool isValidPath(List *path);

    static void toLocalNeighbor(Node *a, Node *b);
};


#endif //TP3_SOLUTION_H
