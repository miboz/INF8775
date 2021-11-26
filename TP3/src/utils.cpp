#ifndef TP2_UTILS_CPP
#define TP2_UTILS_CPP

#include <fstream>
#include "Graph.h"

using namespace std;

const static int RANDOM_SEED = 0;

static Graph *readGraph(const string &filePath) {
    ifstream file(filePath);
    int nbVertices;
    int nbEdges;
    file >> nbVertices;
    file >> nbEdges;
    auto *graph = new Graph(nbVertices, nbEdges);

    int height;
    for (int i = 0; i < nbVertices; i++) {
        file >> height;
        graph->addVertex(i, height);
    }

    int n1;
    int n2;
    for (int i = 0; i < nbEdges; ++i) {
        file >> n1;
        file >> n2;
        graph->addEdge(n1 - 1, n2 - 1);
    }
    return graph;
}

static int getRandomValue(int max) {
    return rand() % max;
}
#endif //TP2_UTILS_CPP
