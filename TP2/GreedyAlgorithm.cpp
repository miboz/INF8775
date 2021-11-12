#include "GreedyAlgorithm.h"
#include "updatable_priority_queue.h"

using namespace std;

void GreedyAlgorithm::solve(Graph *graph) {
    better_priority_queue::updatable_priority_queue<int, Node*> pQ;
    vector<Node> &nodes = graph->getNodes();
    for (int i = 0; i < nodes.size(); ++i) {
        pQ.push(i, &nodes[i]);
    }
    int maxLabel = 0;
    while (!pQ.empty()) {
        Node &node = *pQ.pop_value().priority;
        for (int newLabel = 0; newLabel <= maxLabel; ++newLabel) {
            if (!node.getTotalNeighborsLabelCount().contains(newLabel)) {
                node.setLabel(newLabel);
                if (newLabel == maxLabel) {
                    ++maxLabel;
                }
                for (auto neighbor : node.getNeighbors()) {
                    pQ.update(neighbor->getId(), neighbor);
                }
                break;
            }
        }
    }
}
