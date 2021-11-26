#include <iostream>
#include "Graph.h"

using namespace std;

Graph::Graph(const int &nbVertices, const int &nbEdges) : nbVertices(nbVertices),
                                                          nbEdges(nbEdges),
                                                          adjMatrix(new bool*[nbVertices]) {
    for (int i = 0; i < nbVertices; ++i)
        adjMatrix[i] = new bool[nbVertices]();
    vertices.reserve(nbVertices);
}

Graph::~Graph() {
    for (int i = 0; i < this->nbVertices; ++i) {
        delete[] this->adjMatrix[i];
    }
    delete[] this->adjMatrix;
}

void Graph::addEdge(const int &node1, const int &node2) {
    this->adjMatrix[node1][node2] = true;
    this->adjMatrix[node2][node1] = true;
    vertices[node1].addNeighbor(&vertices[node2]);
    vertices[node2].addNeighbor(&vertices[node1]);
}

void Graph::addVertex(const int &id, const int &height) {
    vertices.emplace_back(id, height);
}

int Graph::getNbVertices() const {
    return nbVertices;
}

int Graph::getNbEdges() const {
    return nbVertices;
}

bool **Graph::getAdjMatrix() const {
    return adjMatrix;
}

std::vector<Vertex> &Graph::getVertices() {
    return vertices;
}
