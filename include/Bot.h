#ifndef BOT_H_ 
#define BOT_H_

#include <vector>

#include "Rooms.h"

class Bot {
public:
    int getStamina();
    bool setStamina(int);
    bool moveToRoom(int);

private:
    int _stamina = -1;
    Room* _curr_room = nullptr;
    std::vector<Room*> _known_rooms;
};

#endif // BOT_H_
