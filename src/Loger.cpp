#include "../include/Loger.h"

#include <string>

Event::~Event() {
    if (_bot_action != nullptr) {
        delete _bot_action;
    }
}

std::string Event::stringify() const {
    std::string result(_bot_action->stringify() + "\nstate ");
    result += std::to_string(_room_snapshot._id) +
              std::to_string(_room_snapshot._iron) +
              std::to_string(_room_snapshot._gold) +
              std::to_string(_room_snapshot._gems) +
              std::to_string(_room_snapshot._exp) + '\n';
    return result;
}

Event::RoomSnapshot::RoomSnapshot(Room& room):
    _id(room.getID()),
    _iron(room.iron()),
    _gold(room.gold()),
    _gems(room.gems()),
    _exp(room.exp()) {}
