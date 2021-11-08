#include "Node.h"

using namespace std;

void Node::addEdge(Node *node) {
    neighbors.push_back(node);
    ++degree;
}

int Node::getLabel() {
    return label;
}
