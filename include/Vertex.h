#ifndef VERTEX_H_
#define VERTEX_H_

#include <map>

class Vertex {
public:
    Vertex(int id);
    void addNeighbour(Vertex&);
    Vertex* getNeighbourPtr(int);
    int getID();
    ~Vertex();

private:
    void addNeighbour(Vertex*);
    int _id;
    std::map <int, Vertex*> _neighbours_ptrs;
};

class VertexManager {
public:
    static VertexManager& getInstance();
    bool exists(int);
    int vertexNum();
    bool addVertex(int, Vertex*);
    bool removeVertex(int);
    Vertex* getVertexPtr(int);

private:
    VertexManager() {}
    VertexManager(const VertexManager&) = delete;
    void operator = (const VertexManager&) = delete;

    std::map <int, Vertex*> _vrtxs_ptrs;
};

#endif // VERTEX_H_
