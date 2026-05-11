#include "../include/Rooms.h"

Room::Room(int id, int iron, int gold, int gems, int exp): Vertex(id) {
    _iron = iron;
    _gold = gold;
    _gems = gems;
    _exp = exp;
}
