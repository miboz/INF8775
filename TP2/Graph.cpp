#include "Graph.h"
#include <iostream>

using namespace std;

Graph::Graph(int& n) : nbNodes(n), nodes(new Node[n]){}

void Graph::addEdge(const int& i, const int& j) {
    nodes[i].addEdge(nodes + j);
}

Graph::~Graph() {
    delete[] nodes;
}

string Graph::toString() {
    if (nbNodes == 0) {
        return "";
    }
    string result = to_string(nodes[0].getLabel());
    for (int i = 1; i < nbNodes; ++i) {
        result += " " + to_string(nodes[i].getLabel());
    }
    return result;
}
