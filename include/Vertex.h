#ifndef VERTEX_H_
#define VERTEX_H_

#include <map>
#include <unordered_map>

class Vertex {
public:
    Vertex(int id);
    bool addNeighbour(Vertex&);
    Vertex* getNeighbourPtr(int);
    Vertex* getLeastIDNeibourPtr() const;
    auto getNeighboursIter() const { return _neighbours_ptrs.begin(); }
    auto getNeighboursEnd()  const { return _neighbours_ptrs.end(); }
    int getID() const;
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

    std::unordered_map <int, Vertex*> _vrtxs_ptrs;
};

#endif // VERTEX_H_
