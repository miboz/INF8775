#ifndef TP2_GRAPH_H
#define TP2_GRAPH_H

#include <string>
#include "Node.h"

class Graph {
private:
    std::vector<Node> nodes;
    std::vector<std::pair<int, int>> edges;
public:
    explicit Graph(int& n);

    void addEdge(const int& i, const int& j);
    int getCost();
    std::vector<Node>& getNodes();
    void reset();
    void setState(const std::vector<int>& state);

    std::string toString();
};


#endif //TP2_GRAPH_H
