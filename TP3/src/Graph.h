#ifndef TP3_GRAPH_H
#define TP3_GRAPH_H

#include <string>
#include <vector>
#include "Vertex.h"

class Graph {

private:
    const int nbVertices;
    const int nbEdges;
    bool **adjMatrix;
    std::vector<Vertex> vertices;

public:
    explicit Graph(const int &nbVertices, const int &nbEdges);
    ~Graph();

    void addEdge(const int &node1, const int &node2);
    void addVertex(const int &id, const int &height);
    [[nodiscard]] int getNbVertices() const;
    [[nodiscard]] int getNbEdges() const;
    [[nodiscard]] bool** getAdjMatrix() const;
    [[nodiscard]] std::vector<Vertex> &getVertices();

};


#endif //TP3_GRAPH_H
