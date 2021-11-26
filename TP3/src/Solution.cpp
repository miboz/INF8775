#include <iostream>
#include "Solution.h"
#include "utils.cpp"

using namespace std;

// TODO : allow local search to change start and end node, also add a way to get out of local max
void Solution::solve(Graph *g) {
    List *path = posaHeuristic(g);
    bool** adjMatrix = g->getAdjMatrix();
    int nbVertices = g->getNbVertices();
    int bestScore = getScore(path);
    // TODO: remove score print for submission
    cout << "score :" << bestScore << endl;
//    cout << path->toString();

    while (bestScore != nbVertices) {
        int bestLocalScore = 0;
        Node *bestA = nullptr;
        Node *bestB = nullptr;
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
                    bestA = a;
                    bestB = b;
                }
                toLocalNeighbor(a, aNext);
            }
            visited.insert(v);
        }
        if (bestLocalScore != 0) {
            toLocalNeighbor(bestA, bestB);
            if (bestLocalScore > bestScore) {
                bestScore = bestLocalScore;
                // TODO: remove score print for submission
                cout << "score :" << bestScore << endl;
//                cout << path->toString();
            }
        }
    }

    delete path;
}


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

            if (tryExtendPath(path, true)) continue;
            if (tryExtendPath(path, false)) continue;

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
        if (node->value->getHeight() <= maxHeight) continue;
        maxHeight = node->value->getHeight();
        ++score;
    }
    return score;
}

// TODO: remove validation after asserting that everything works fine
bool Solution::isValidPath(List *path) {
    set<Vertex*> visited;
    Node *tail = path->getTail();
    for (Node *node = path->getHead(); node != tail; node = node->next) {
        if (visited.contains(node->value)) {
            cout << "ERROR: visited vertex twice" << node->value->getId() << endl;
            return false;
        }
        visited.insert(node->value);
        bool isNeighbor = false;
        for (Vertex *neighbor : node->value->getNeighbors()) {
            if (neighbor != node->next->value) continue;
            isNeighbor = true;
            break;
        }
        if (!isNeighbor) {
            cout << "ERROR: vertex " << node->value->getId() << " is not a neighbor of "
            << node->next->value->getId() << endl;
            return false;
        }
    }
    return true;
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

