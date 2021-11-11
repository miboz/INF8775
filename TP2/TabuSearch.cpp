#include "TabuSearch.h"
#include "GreedyAlgorithm.h"
#include <list>
#include <set>
#include <climits>

using namespace std;

void TabuSearch::solve(Graph *graph) {
    GreedyAlgorithm::solve(graph);
    bool success;
    vector<int> bestSolution;
    bestSolution.reserve(graph->getNodes().size());
    do {
        graph->saveSolution(bestSolution);
        success = repairGraph(graph, reduceDistinctLabelCount(graph));
    } while(success);
    graph->setState(bestSolution);
}

int TabuSearch::reduceDistinctLabelCount(Graph* graph) {
    list<Node*> nodesToChange;
    vector<Node>& nodes = graph->getNodes();
    map<int, int> conflictCountByLabel;
    int labelToRemove = graph->getCost() - 1;
    for (auto& node : nodes) {
        if (node.getLabel() == labelToRemove) {
            for (auto& neighborCount : node.getTotalNeighborsLabelCount()) {
                if (!conflictCountByLabel.contains(neighborCount.first))
                    conflictCountByLabel[neighborCount.first] = 0;
                conflictCountByLabel[neighborCount.first] += neighborCount.second;
            }
            nodesToChange.push_back(&node);
        } else if (!conflictCountByLabel.contains(node.getLabel()))
            // In case of a label that is not adjacent to the label to remove
            conflictCountByLabel[node.getLabel()] = 0;
    }
    int bestLabelConflictsCount = INT_MAX;
    int bestLabel;
    for (auto& labelConflicts : conflictCountByLabel) {
        if (labelConflicts.second < bestLabelConflictsCount) {
            bestLabelConflictsCount = labelConflicts.second;
            bestLabel = labelConflicts.first;
        }
    }
    for (auto& node : nodesToChange)
        node->setLabel(bestLabel);
    return bestLabelConflictsCount;
}

bool TabuSearch::repairGraph(Graph* graph, int conflictCount) {
    set<pair<int, int>> tabuSet;
    map<int, list<pair<int, int>>> tabuExpirations;
    int bestConflictCount = conflictCount;
    int iteration = 0;
    int iterationsSinceLastImprovement = 0;
    int distinctLabelsCount = graph->getCost();
    // TODO check the case where the graph has another label less after the repair
    while (iterationsSinceLastImprovement != MAX_ITERATIONS_WITHOUT_IMPROVEMENT) {
        // get best neighbor
        int nodeId;
        int newLabel;
        int minDelta = INT_MAX;
        for (auto& node : graph->getNodes()) {
            for (int i = 0; i < distinctLabelsCount; ++i) {
                int label = node.getLabel();
                if (label == i || tabuSet.contains(make_pair(node.getId(), i))) continue;
                auto& neighborCount = node.getTotalNeighborsLabelCount();
                int delta = neighborCount[i] - neighborCount[label];
                if (delta < minDelta) {
                    minDelta = delta;
                    nodeId = node.getId();
                    newLabel = i;
                }

            }
        }
        if (minDelta == INT_MAX) return false;

        // change state
        graph->getNodes()[nodeId].setLabel(newLabel);
        conflictCount += minDelta;


        // add to tabu list
        pair<int, int> tabu = make_pair(nodeId, newLabel);
        tabuSet.insert(tabu);
        int expiration = iteration + ALPHA * conflictCount + getRandomNumber();
        if (!tabuExpirations.contains(expiration))
            tabuExpirations[expiration] = list<pair<int, int>>();
        tabuExpirations[expiration].push_back(tabu);

        // remove expired tabu
        if (tabuExpirations.contains(iteration)) {
            for (auto& tabuToRemove : tabuExpirations[iteration])
                tabuSet.erase(tabuToRemove);
            tabuExpirations.erase(iteration);
        }

        // end condition
        if (conflictCount < bestConflictCount) {
            // TODO fix the negative conflict count case (for real)
            if (conflictCount == 0) return true;
            bestConflictCount = conflictCount;
            // Will cancel out to be 0 in the next instruction
            iterationsSinceLastImprovement = -1;
        }

        ++iterationsSinceLastImprovement;
        ++iteration;
    }

    return false;
}

int TabuSearch::getRandomNumber() {
    return (rand() % G) + 1;
}
