#ifndef TP2_NODE_H
#define TP2_NODE_H

# include <vector>
#include <map>

class Node {
private:
    std::vector<Node*> neighbors;
    int degree = 0;
    int label = -1;
    std::map<int, int> totalNeighborsLabelCount;


public:
    void addEdge(Node* node);
    int getLabel();
};


#endif //TP2_NODE_H
