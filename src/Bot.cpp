#include "../include/Bot.h"

#include "../include/Rooms.h"

Bot::Bot() {
    _curr_room = VertexManager::getInstance().getVertexPtr(0);
    if (_curr_room != nullptr) {
        for (auto neighbour = _curr_room->getNeighboursIter(); neighbour != _curr_room->getNeighboursEnd(); neighbour++) {
            _visible_rooms_ptrs[neighbour->first] = (neighbour->second);
        }
    }
}

int Bot::currRoomID() {
    return _curr_room->getID();
}

bool Bot::moveToRoom(int id) {
    if ((_curr_room->getNeighbourPtr(id) == nullptr) || (_curr_room == nullptr)) {
        return false;
    }
    static_cast<Room*>(_curr_room)->visited() = true;
    _curr_room = _curr_room->getNeighbourPtr(id);
    for (auto neighbour = _curr_room->getNeighboursIter(); neighbour != _curr_room->getNeighboursEnd(); neighbour++) {
        _visible_rooms_ptrs[neighbour->first] = (neighbour->second);
    }
    return true;
}

bool Bot::seenRoom(int id) {
    return _visible_rooms_ptrs.contains(id);
}

Vertex* Bot::getLeastIDSeenRoom() {
    return _visible_rooms_ptrs.begin()->second;
}

bool ActingBot::setStamina(int stamina) {
    if (stamina < 2 && stamina > 255) {
        return false;
    }
    _stamina = stamina;
    return true;
}

bool ActingBot::act(Action* act_ptr) {
    return act_ptr->perform();
}

bool ActingBot::Go::perform() {
    _bt->_stamina -= 1;
    return _bt->moveToRoom(_id);
}

std::string ActingBot::Go::stringify() {
    std::string result("go ");
    return result + std::to_string(_id);
}

bool ActingBot::Collect::perform() {
    VertexManager* vm_ptr = &VertexManager::getInstance();
    Room* curr_room = static_cast<Room*>(vm_ptr->getVertexPtr(_bt->currRoomID()));
    switch (_resource) {
        case Resource::Iron: {
            _bt->_collected_iron += curr_room->iron();
            curr_room->iron() = 0;
            break;
        }
        case Resource::Gold: {
            _bt->_collected_gold += curr_room->gold();
            curr_room->gold() = 0;
            break;
        }
        case Resource::Gems: {
            _bt->_collected_gems += curr_room->gems();
            curr_room->gems() = 0;
            break;
        }
        case Resource::Exp: {
            _bt->_collected_exp += curr_room->exp();
            curr_room->exp() = 0;
            break;
        }
    }
    if (static_cast<Room*>(VertexManager::getInstance().getVertexPtr(_bt->currRoomID()))->visited()) {
        _bt->_stamina -= 1;
    }
    return (_bt->getStamina() > 0);
}

std::string ActingBot::Collect::stringify() {
    std::string result("collect ");
    switch (_resource) {
        case Resource::Iron: {
            result += "iron";
            break;
        }
        case Resource::Gold: {
            result += "gold";
            break;
        }
        case Resource::Gems: {
            result += "gems";
            break;
        }
        case Resource::Exp: {
            result += "exp";
            break;
        }
    }
    return result;
}
