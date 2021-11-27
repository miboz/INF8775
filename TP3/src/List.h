#ifndef TP3_LIST_H
#define TP3_LIST_H

#include "Vertex.h"
#include <string>

struct Node {
    explicit Node(Vertex *value);

    void swap();

    Vertex *value;
    Node *next = nullptr;
    Node *prev = nullptr;
};

class List {
private:
    Node *head = nullptr;
    Node *tail = nullptr;
    Node **idToNode;
    int size = 0;

public:
    explicit List(int finalSize);

    ~List();

    void pushBack(Vertex *value);
    void pushFront(Vertex *value);
    Node *getHead();
    Node *getTail();
    Node *getNodeFromId(int id);
    int getSize();
    bool contains(Vertex *value);
    void posaOperation(Node *neighborNode);
    void reverse();
    void save(int* data, int dataSize) const;
    void load(const int* data, int dataSize);
    std::string toString(bool printFlag);
};

#endif //TP3_LIST_H
