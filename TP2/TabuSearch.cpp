#include "TabuSearch.h"
#include "GreedyAlgorithm.h"
#include <list>
#include <set>
#include <iostream>
#include <climits>

using namespace std;

int TabuSearch::maxIterationsWithoutImprovement;

void TabuSearch::solve(Graph *graph) {
    GreedyAlgorithm::solve(graph);
    bool success;
    vector<int> bestSolution;
    bestSolution.reserve(graph->getNodes().size());
    maxIterationsWithoutImprovement = graph->getNodes().size() * C;
    do {
        graph->saveSolution(bestSolution);
        int nbConflicts = reduceDistinctLabelCount(graph);
        if (nbConflicts == 0) continue;
        success = repairGraph(graph, nbConflicts);
    } while(success);
    graph->setState(bestSolution);
}

int TabuSearch::reduceDistinctLabelCount(Graph* graph) {
    list<Node*> nodesToChange;
    vector<Node>& nodes = graph->getNodes();
    int labelToRemove = graph->getCost() - 1;
    vector<int> conflictCount(labelToRemove, 0);
    for (auto& node : nodes) {
        if (node.getLabel() == labelToRemove) {
            for (auto& neighborCount : node.getTotalNeighborsLabelCount()) {
                conflictCount[neighborCount.first] += neighborCount.second;
            }
            nodesToChange.push_back(&node);
        }
    }
    int bestLabelConflictsCount = INT_MAX;
    int bestLabel;
    for (int i = 0; i < conflictCount.size(); ++i) {
        if (conflictCount[i] < bestLabelConflictsCount) {
            bestLabelConflictsCount = conflictCount[i];
            bestLabel = i;
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
    while (iterationsSinceLastImprovement != maxIterationsWithoutImprovement) {
        // get best neighbor
        int nodeId;
        int newLabel;
        int minDelta = INT_MAX;
        for (auto& node : graph->getNodes()) {
            for (int i = 0; i < distinctLabelsCount; ++i) {
                int label = node.getLabel();
                if (label == i || tabuSet.contains(make_pair(node.getId(), i))) continue;
                auto& neighborCount = node.getTotalNeighborsLabelCount();
                int conflictsToAdd = neighborCount.contains(i) ? neighborCount[i] : 0;
                int conflictsToRemove = neighborCount.contains(label) ? neighborCount[label] : 0;
                int delta = conflictsToAdd - conflictsToRemove;
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
