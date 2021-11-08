#ifndef TP2_UTILS_CPP
#define TP2_UTILS_CPP

#include <fstream>
#include "Graph.h"

using namespace std;

static Graph* readGraph(const string& filePath) {
    ifstream file(filePath);
    int n;
    file >> n;
    Graph* graph = new Graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            bool isEdge;
            file >> isEdge;
            if (isEdge) {
                graph->addEdge(i, j);
            }
        }
    }
    return graph;
}
#endif //TP2_UTILS_CPP