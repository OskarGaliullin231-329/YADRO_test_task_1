#ifndef ROOMS_H_
#define ROOMS_H_

#include "Vertex.h"

class Room: public Vertex {
public:
    Room(int, int, int, int, int);
    void visit() { _visited = true; }
    void unvisit() { _visited = false; }

private:
    int _iron;
    int _gold;
    int _gems;
    int _exp;
    bool _visited = false;
};

#endif // ROOMS_H_
