#include <iostream>
#include <chrono>
#include "Graph.h"
#include "utils.cpp"
#include "GreedyAlgorithm.h"
#include "BranchAndBound.h"
#include "TabuSearch.h"

using namespace std;

bool printFlag = false;
bool timeFlag = false;
string algorithmType;
string graphPath;

void parseFlags(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) {
            printFlag = true;
        } else if (strcmp(argv[i], "-t") == 0) {
            timeFlag = true;
        } else if (strcmp(argv[i], "-a") == 0) {
            algorithmType = argv[i + 1];
        } else if (strcmp(argv[i], "-e") == 0) {
            graphPath = argv[i + 1];
        }
    }
}

void solve(Graph* graph) {
    if (algorithmType == "glouton") {
        GreedyAlgorithm::solve(graph);
    }
    if (algorithmType == "branch_bound") {
        BranchAndBound::solve(graph);
    }
    TabuSearch::solve(graph);
}

int main(int argc, char *argv[]) {
    parseFlags(argc, argv);
    Graph* graph = readGraph(graphPath);
    auto start = chrono::steady_clock::now();

    solve(graph);

    auto end = chrono::steady_clock::now();
    auto diff = end - start;

    if (printFlag) {
        cout << graph->toString() << endl;
    }
    if (timeFlag) {
        cout <<  chrono::duration <double, milli> (diff).count() << endl;
    }
    delete graph;
    return 0;
}