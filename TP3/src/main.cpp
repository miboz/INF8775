#include <iostream>
#include <cstring>
#include "Graph.h"
#include "utils.cpp"
#include "Solution.h"

bool printFlag = false;
string graphPath;

void parseFlags(const int &argc, char **&argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) {
            printFlag = true;
        } else if (strcmp(argv[i], "-e") == 0) {
            graphPath = argv[i + 1];
        }
    }
}

int main(int argc, char *argv[]) {
    parseFlags(argc, argv);
    srand(RANDOM_SEED);
    Graph *graph = readGraph(graphPath);
    Solution::solve(graph);
    delete graph;
}
