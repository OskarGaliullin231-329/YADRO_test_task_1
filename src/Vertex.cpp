#include "../include/Vertex.h"

Vertex::Vertex(int id): _id(id) {
    if (!VertexManager::getInstance().addVertex(id, this)) {
        _id = -1;
    }
}

void Vertex::addNeighbour(Vertex* vrtx) {
    vrtx->_neighbours_ptrs[_id] = this;
}

void Vertex::addNeighbour(Vertex& vrtx) {
    _neighbours_ptrs[vrtx._id] = &vrtx;
    addNeighbour(&vrtx);
}

int Vertex::getID() {
    return _id;
}

VertexManager& VertexManager::getInstance() {
    static VertexManager _instance;
    return _instance;
}

bool VertexManager::exists(int id) {
    return _vrtxs_ptrs.contains(id);
}

int VertexManager::vertexNum() {
    return _vrtxs_ptrs.size();
}

bool VertexManager::addVertex(int id, Vertex* vrtx_ptr) {
    if (exists(id)) {
        return false;
    }
    _vrtxs_ptrs[id] = vrtx_ptr;
    return true;
}

bool VertexManager::removeVertex(int id) {
    if (!exists(id)) {
        return false;
    }
    _vrtxs_ptrs.erase(id);
    return true;
}

Vertex* VertexManager::getVertex(int id) {
    if (!exists(id)) {
        return nullptr;
    }
    return _vrtxs_ptrs[id];
}
