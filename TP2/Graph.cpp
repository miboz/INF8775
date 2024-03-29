#include <iostream>
#include <set>
#include "Graph.h"

using namespace std;

Graph::Graph(int &n) {
    nodes.reserve(n);
    for (int i = 0; i < n; ++i)
        nodes.emplace_back(i);
}

void Graph::addEdge(const int &i, const int &j) {
    nodes[i].addEdge(&nodes[j]);
    nodes[j].addEdge(&nodes[i]);
}

string Graph::toString() {
    int nbNodes = nodes.size();
    if (nbNodes == 0) {
        return "";
    }
    string result = to_string(getCost()) + "\n";
    result += to_string(nodes[0].getLabel());
    for (int i = 1; i < nbNodes; ++i) {
        vector<Node*> &neighbours = nodes[i].getNeighbors();
        int label = nodes[i].getLabel();
        result += " " + to_string(label);
    }
    return result;
}

vector<Node> &Graph::getNodes() {
    return nodes;
}

int Graph::getCost() {
    set<int> distinctLabels;
    for (auto &node : nodes) {
        distinctLabels.insert(node.getLabel());
    }
    return distinctLabels.size();
}

void Graph::reset() {
    for (auto &node : nodes)
        node.reset();
}

void Graph::setState(const vector<int> &state) {
    for (int i = 0; i < state.size(); ++i) {
        nodes[i].setLabel(state[i]);
    }
}

void Graph::saveSolution(vector<int> &v) {
    if (v.empty())
        for ( auto &node : nodes)
            v.push_back(node.getLabel());
    else
        for (int i = 0; i < v.size(); ++i)
            v[i] = nodes[i].getLabel();
}
