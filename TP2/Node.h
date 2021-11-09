#ifndef TP2_NODE_H
#define TP2_NODE_H

# include <vector>
#include <map>

class Node {
private:
    static const int UNLABELLED = -1;
    std::vector<Node*> neighbors;
    int id = 0;
    int degree = 0;
    int label = UNLABELLED;
    std::map<int, int> totalNeighborsLabelCount;


public:
    explicit Node(int id);
    void addEdge(Node* node);
    int getLabel() const;
    int getId() const;
    std::map<int, int>& getTotalNeighborsLabelCount();
    std::vector<Node*>& getNeighbors();
    bool operator>(const Node &node) const;
    bool operator<(const Node &node) const;

    void setLabel(int label);
};


#endif //TP2_NODE_H
