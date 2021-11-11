#include <stack>
#include <set>
#include <iostream>
#include "updatable_priority_queue.h"
#include "BranchAndBound.h"
#include "GreedyAlgorithm.h"

using namespace std;

void BranchAndBound::solve(Graph *graph) {
    GreedyAlgorithm::solve(graph);
    int upperBound = graph->getCost();
    // With two labels or fewer, we know that the greedy Algorithm has found the best solution
    if (upperBound <= 2) {
        return;
    }
    vector<int> bestSolution;
    vector<Node>& nodes = graph->getNodes();
    bestSolution.reserve(nodes.size());
    for (auto & node : nodes) {
        bestSolution.push_back(node.getLabel());
    }
    graph->reset();
    better_priority_queue::updatable_priority_queue<int, Node*> pQ;
    for (int i = 0; i < nodes.size(); ++i) {
        pQ.push(i, &nodes[i]);
    }
    stack<StackElement> stackNodesToProcess;
    stack<Node*> processedNodes;

    int level = -1;
    stackNodesToProcess.push(StackElement{0, 0, 1});
    while (!stackNodesToProcess.empty()) {
        StackElement stackElement = stackNodesToProcess.top();
        stackNodesToProcess.pop();
        if (stackElement.currentCost >= upperBound) {
            continue;
        }
        if (stackElement.level > level) {
            // Go down
            Node& node = *pQ.pop_value().priority;
            processedNodes.push(&node);
            node.setLabel(stackElement.newLabel);
            for (auto neighbor : node.getNeighbors()) {
                pQ.update(neighbor->getId(), neighbor);
            }
        } else {
            int limit = level - stackElement.level;
            set<Node*> nodesToUpdate;
            Node* currentNode;
            for (int i = 0; i <= limit; ++i) {
                currentNode = processedNodes.top();
                processedNodes.pop();
                int newLabel;
                if (i != limit) {
                    pQ.push(currentNode->getId(), currentNode);
                    newLabel = Node::UNLABELLED;
                } else {
                    newLabel = stackElement.newLabel;
                }
                currentNode->setLabel(newLabel);
                for (auto neighbor : currentNode->getNeighbors()) {
                    nodesToUpdate.insert(neighbor);
                }
            }
            for (auto node : nodesToUpdate) {
                pQ.update(node->getId(), node);
            }
            processedNodes.push(currentNode);
        }
        level = stackElement.level;
        // New best solution found
        if (pQ.empty()) {
            upperBound = stackElement.currentCost;
            for (int i = 0; i < nodes.size(); ++i) {
                bestSolution[i] = nodes[i].getLabel();
            }
            continue;
        }
        // Push the next node to process with valid label in the stack
        auto nextNodeTotalNeighborsLabelCount = pQ.top().priority->getTotalNeighborsLabelCount();
        for (int i = 0; i <= stackElement.currentCost; ++i) {
            if (!nextNodeTotalNeighborsLabelCount.contains(i)) {
                stackNodesToProcess.push(StackElement{
                        stackElement.level + 1,
                        i,
                        stackElement.currentCost + (i == stackElement.currentCost)});
            }
        }
    }
    graph->setState(bestSolution);
}
