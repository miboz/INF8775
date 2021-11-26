#include "Vertex.h"

using namespace std;


Vertex::Vertex(int id, int height) : id(id), height(height) {}

void Vertex::addNeighbor(Vertex *neighbor) {
    neighbors.push_back(neighbor);
}

const std::vector<Vertex *> &Vertex::getNeighbors() const {
    return neighbors;
}

int Vertex::getId() const {
    return id;
}

int Vertex::getHeight() const {
    return height;
}
