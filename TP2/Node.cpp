#include "Node.h"

using namespace std;

Node::Node(int id) : id(id) {}

void Node::addEdge(Node* node) {
    neighbors.push_back(node);
    ++degree;
}

int Node::getLabel() const {
    return label;
}

bool Node::operator>(const Node &node) const {
    return totalNeighborsLabelCount.size() > node.totalNeighborsLabelCount.size()||
           totalNeighborsLabelCount.size() == node.totalNeighborsLabelCount.size() &&
           degree > node.degree;
}

bool Node::operator<(const Node &node) const {
    return totalNeighborsLabelCount.size() < node.totalNeighborsLabelCount.size()||
           totalNeighborsLabelCount.size() == node.totalNeighborsLabelCount.size() &&
           degree < node.degree;
}

map<int, int>& Node::getTotalNeighborsLabelCount() {
    return totalNeighborsLabelCount;
}

std::vector<Node*>& Node::getNeighbors() {
    return neighbors;
}

int Node::getId() const {
    return id;
}

void Node::setLabel(int newLabel) {
    int oldLabel = label;
    label = newLabel;
    for (auto neighbor : neighbors) {
        auto& labelCount = neighbor->getTotalNeighborsLabelCount();
        if (oldLabel != UNLABELLED) {
            --labelCount[oldLabel];
            if (labelCount[oldLabel] == 0)
                labelCount.erase(oldLabel);
        }
        if (!labelCount.contains(newLabel))
            labelCount[newLabel] = 1;
        else
            ++labelCount[newLabel];
    }
}
