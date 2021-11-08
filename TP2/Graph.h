#ifndef TP2_GRAPH_H
#define TP2_GRAPH_H

#include <string>
#include "Node.h"

class Graph {
private:
    int nbNodes;
    Node* nodes;
public:
    explicit Graph(int& n);
    ~Graph();

    void addEdge(const int& i, const int& j);

    std::string toString();
};


#endif //TP2_GRAPH_H
