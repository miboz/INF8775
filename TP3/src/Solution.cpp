#include <iostream>
#include "Solution.h"
#include "utils.cpp"

using namespace std;

// Greedy local search
void Solution::solve(Graph *g, bool printFlag) {
    List *path = posaHeuristic(g);
    bool** adjMatrix = g->getAdjMatrix();
    int nbVertices = g->getNbVertices();
    int* bestLocalPath = new int[nbVertices];
    int bestScore = getScore(path);
    cout << path->toString(printFlag);

    while (bestScore != nbVertices) {
        int bestLocalScore = 0;
        exploreNeighbors(path, bestLocalScore, bestLocalPath, adjMatrix);
        explorePosaNeighbors(path, bestLocalScore, bestLocalPath, adjMatrix);
        path->reverse();
        explorePosaNeighbors(path, bestLocalScore, bestLocalPath, adjMatrix);
        path->reverse();
        if (bestLocalScore <= bestScore) break;
        path->load(bestLocalPath, nbVertices);
        bestScore = bestLocalScore;
            cout << path->toString(printFlag);
    }
    delete[] bestLocalPath;

    delete path;
}

// Greedy algorithm to add vertices to the path, when impossible, exploring the posa transformations with dfs structure
// Inspired from https://www.sciencedirect.com/science/article/pii/S0012365X06005097#bib5
List* Solution::posaHeuristic(Graph *g) {
    const int nbVertices = g->getNbVertices();
    vector<Vertex> &vertices = g->getVertices();
    List *path;
    do {
        path = new List(nbVertices);
        Vertex &randomVertex = vertices[getRandomValue(nbVertices)];
        const vector<Vertex*> &neighbors = randomVertex.getNeighbors();
        path->pushBack(&randomVertex);
        path->pushBack(neighbors[getRandomValue(neighbors.size())]);

        while (path->getSize() != nbVertices) {

            // add vertex to path greedily
            if (tryExtendPath(path, true)) continue;
            if (tryExtendPath(path, false)) continue;

            // dfs exploration with posa transformations
            set<Node*> visitedEndPoints;
            if (posaSearch(path, visitedEndPoints)) continue;
            path->reverse();
            if (!posaSearch(path, visitedEndPoints)) break;
        }
        if (path->getSize() != nbVertices) delete path;
    } while(path->getSize() != nbVertices);

    return path;
}

bool Solution::tryExtendPath(List *path, bool isTail) {
    Node* endpoint = isTail ? path->getTail() : path->getHead();
    for (Vertex* neighbor : endpoint->value->getNeighbors()) {
        if (path->contains(neighbor)) continue;
        if (isTail) path->pushBack(neighbor);
        else path->pushFront(neighbor);
        return true;
    }
    return false;
}

bool Solution::posaSearch(List *path, set<Node *> &visitedEndpoints) {
    Node *endpoint = path->getTail();
    visitedEndpoints.insert(endpoint);

    for (auto neighbor : endpoint->value->getNeighbors()) {
        if (path->getNodeFromId(neighbor->getId()) == nullptr) return true;
    }

    for (auto neighbor : endpoint->value->getNeighbors()) {
        Node *neighborNode = path->getNodeFromId(neighbor->getId());
        if (visitedEndpoints.contains(neighborNode->next)) continue;

        path->posaOperation(neighborNode);
        if (Solution::posaSearch(path, visitedEndpoints)) return true;
        path->posaOperation(neighborNode);
    }
    return false;
}

int Solution::getScore(List *path) {
    int score = 0;
    int maxHeight = -1;
    for (Node *node = path->getHead(); node != nullptr; node = node->next) {
        if (node->value->getHeight() < maxHeight) continue;
        maxHeight = node->value->getHeight();
        ++score;
    }
    return score;
}

void Solution::toLocalNeighbor(Node *a, Node *b) {
    a->next->prev = b->next;
    b->next->prev = a->next;
    Node *currentNode = a->next;
    a->next = b;
    b->next = a;
    do {
        currentNode->swap();
        currentNode = currentNode->prev;
    } while (currentNode != a);
}

void Solution::exploreNeighbors(List *path, int &bestLocalScore, int *bestLocalPath, bool** adjMatrix) {
    set<Vertex*> visited;
    for (Node *a = path->getHead(); a->next->next != nullptr; a = a->next) {
        Vertex *v = a->value;
        for (Vertex *w : v->getNeighbors()) {
            if (visited.contains(w)) continue;
            Node *b = path->getNodeFromId(w->getId());
            if (a->next == b) continue;
            if (b->next == nullptr) continue;
            if (!adjMatrix[a->next->value->getId()][b->next->value->getId()]) continue;
            Node *aNext = a->next;
            toLocalNeighbor(a, b);
            int score = getScore(path);
            if (score > bestLocalScore) {
                bestLocalScore = score;
                path->save(bestLocalPath, path->getSize());
            }
            toLocalNeighbor(a, aNext);
        }
        visited.insert(v);
    }
}

void Solution::explorePosaNeighbors(List *path, int &bestLocalScore, int *bestLocalPath, bool **adjMatrix) {
    Node* tail = path->getTail();
    for (auto neighbor : tail->value->getNeighbors()) {
        Node *neighborNode = path->getNodeFromId(neighbor->getId());
        path->posaOperation(neighborNode);
        exploreNeighbors(path, bestLocalScore, bestLocalPath, adjMatrix);
        path->posaOperation(neighborNode);
    }
}

