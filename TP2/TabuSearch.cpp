#include "TabuSearch.h"
#include "GreedyAlgorithm.h"
#include <list>

using namespace std;

void TabuSearch::solve(Graph *graph) {
    GreedyAlgorithm::solve(graph);
    bool success;
    do {
        reduceDistinctLabelCount(graph);
        success = repairGraph(graph);
    } while(!success);
}

void TabuSearch::reduceDistinctLabelCount(Graph* graph) {
    list<Node*> nodesToChange;
    vector<Node>& nodes = graph->getNodes();
    better_priority_queue::updatable_priority_queue<int, int*> conflictPQ;
    int labelToRemove = graph->getCost() - 1;
    for (auto& node : nodes) {
        if (node.getLabel() == labelToRemove) {
            for (auto& neighbor : node.getNeighbors())
                incrementConflictCount(conflictPQ, neighbor->getLabel());
            nodesToChange.push_back(&node);
        } else
            // In case of a label that is not adjacent to the label to remove
            conflictPQ.push(node.getLabel(), new int(1), true);
    }
    int bestLabel = conflictPQ.top().key;
    for (auto& node : nodesToChange)
        node->setLabel(bestLabel);
    conflictPQ.clear();
}

bool TabuSearch::repairGraph(Graph* graph) {
    return true;
}

void TabuSearch::incrementConflictCount(better_priority_queue::updatable_priority_queue<int, int*>& conflictPQ,
                                        int label) {
    // Using the highest priority to determine which label has the least conflicts
    // because the priority queue is a max heap
    bool isNew = conflictPQ.push(label, new int(0), true);
    if (!isNew)
        conflictPQ.update(label, &--*conflictPQ.get_priority(label).second);
}
