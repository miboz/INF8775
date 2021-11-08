#include <iostream>
#include "Graph.h"
#include "utils.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    string graphPath = "instances/ex5_0";
    Graph* graph = readGraph(graphPath);
    cout << graph->toString() << endl;
    delete graph;
    return 0;
}