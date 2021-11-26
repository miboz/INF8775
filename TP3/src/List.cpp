#include <sstream>
#include "List.h"

using namespace std;

List::List(int finalSize) : idToNode(new Node*[finalSize]()) {}

List::~List() {
    delete[] idToNode;
    Node *p = head;
    while (p != nullptr) {
        Node *q = p->next;
        delete p;
        p = q;
    }
}

void List::pushBack(Vertex *value) {
    Node* newNode = new Node(value);
    idToNode[value->getId()] = newNode;
    if (size == 0) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    ++size;
}

void List::pushFront(Vertex *value) {
    Node* newNode = new Node(value);
    idToNode[value->getId()] = newNode;
    if (size == 0) {
        head = newNode;
        tail = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
    ++size;
}

Node *List::getHead() {
    return head;
}

Node *List::getTail() {
    return tail;
}

Node *List::getNodeFromId(int id) {
    return idToNode[id];
}

int List::getSize() {
    return size;
}

bool List::contains(Vertex *value) {
    return idToNode[value->getId()] != nullptr;
}

void List::posaOperation(Node *neighborNode) {
    tail->next = neighborNode;
    Node *newTail = neighborNode->next;
    neighborNode->next = tail;
    newTail->prev = nullptr;

    Node *currentNode = newTail;
    do {
        currentNode->swap();
        currentNode = currentNode->prev;
    } while (currentNode != neighborNode);
    tail = newTail;
}

void List::reverse() {
    Node *currentNode = head;
    do {
        currentNode->swap();
        currentNode = currentNode->prev;
    } while (currentNode != nullptr);
    currentNode = tail;
    tail = head;
    head = currentNode;
}

string List::toString() {
    stringstream ss;
    for (Node *node = head; node != nullptr; node = node->next)
        ss << node->value->getId() + 1 << " ";
    ss << endl;
    return ss.str();
}

Node::Node(Vertex *value): value(value) {}

void Node::swap() {
    Node *p = prev;
    prev = next;
    next = p;
}
