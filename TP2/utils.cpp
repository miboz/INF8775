#ifndef TP2_UTILS_CPP
#define TP2_UTILS_CPP

#include <fstream>
#include "Graph.h"

using namespace std;

static void skipNLines(ifstream& file, int n) {
    for (int i = 0; i < n; ++i) {
        file.ignore(numeric_limits<streamsize>::max(), file.widen('\n'));
    }
}

static Graph* readGraph(const string& filePath) {
    ifstream file(filePath);
    skipNLines(file, 11);
    file.ignore(7);
    int nbNodes;
    int nbEdges;
    file >> nbNodes;
    file >> nbEdges;
    Graph* graph = new Graph(nbNodes);
    skipNLines(file, 2);
    int e1;
    int e2;
    for (int i = 0; i < nbEdges; ++i) {
        file.ignore(2);
        file >> e1;
        file >> e2;
        skipNLines(file, 1);
        graph->addEdge(e1 - 1, e2 - 1);
    }
    return graph;
}
#endif //TP2_UTILS_CPP