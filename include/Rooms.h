#ifndef ROOMS_H_
#define ROOMS_H_

#include "Vertex.h"

class Room: public Vertex {
public:
    Room(int, int, int, int, int);
    
    int&  iron()    { return _iron; }
    int&  gold()    { return _gold; }
    int&  gems()    { return _gems; }
    int&  exp()     { return _exp; }
    bool& visited() { return _visited; }

private:
    int _iron;
    int _gold;
    int _gems;
    int _exp;
    bool _visited = false;
};

#endif // ROOMS_H_
