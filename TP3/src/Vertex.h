#ifndef TP3_VERTEX_H
#define TP3_VERTEX_H

#include <vector>


class Vertex {
private:
    std::vector<Vertex*> neighbors;
    int id;
    int height;

public:
    explicit Vertex(int id, int height);

    void addNeighbor(Vertex* neighbor);
    [[nodiscard]] const std::vector<Vertex*> &getNeighbors() const;
    [[nodiscard]] int getId() const;
    [[nodiscard]] int getHeight() const;
};


#endif //TP3_VERTEX_H
