#include <iostream>
#include <set>
#include "Graph.h"

using namespace std;

Graph::Graph(int& n) : nbNodes(n) {
    nodes.reserve(nbNodes);
    for (int i = 0; i < nbNodes; ++i)
        nodes.emplace_back(i);
}

void Graph::addEdge(const int& i, const int& j) {
    nodes[i].addEdge(&nodes[j]);
}

string Graph::toString() {
    if (nbNodes == 0) {
        return "";
    }
    string result = to_string(getCost()) + "\n";
    result += to_string(nodes[0].getLabel());
    for (int i = 1; i < nbNodes; ++i) {
        // neigbours
        vector<Node*>& neighbours = nodes[i].getNeighbors();
        // TODO remove after testing
        for(Node* n : neighbours) {
            if (n->getLabel() == nodes[i].getLabel()) {
                cout << "ERROR: " << n->getId() << " " << nodes[i].getId() << endl;
            }
        }
        int label = nodes[i].getLabel();
        result += " " + to_string(label);
    }
    return result;
}

vector<Node>& Graph::getNodes() {
    return nodes;
}

int Graph::getCost() {
    set<int> distinctLabels;
    for (int i = 0; i < nbNodes; ++i) {
        distinctLabels.insert(nodes[i].getLabel());
    }
    return distinctLabels.size();
}

void Graph::reset() {
    for (auto& node : nodes)
        node.reset();
}

void Graph::setState(const vector<int>& state) {
    for (int i = 0; i < state.size(); ++i) {
        nodes[i].setLabel(state[i]);
    }
}
