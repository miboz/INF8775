#include <iostream>
#include <set>
#include "Graph.h"

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
    set<int> distinctLabels;
    string result = to_string(nodes[0].getLabel());
    for (int i = 1; i < nbNodes; ++i) {
        int label = nodes[i].getLabel();
        result += " " + to_string(label);
        distinctLabels.insert(label);
    }
    result = to_string(distinctLabels.size()) + "\n" + result;
    return result;
}
