#include "../include/Bot.h"

Bot::Bot(int room_num) {
    _curr_room = VertexManager::getInstance().getVertexPtr(room_num);
}

int Bot::currRoomID() {
    return _curr_room->getID();
}

bool Bot::moveToRoom(int id) {
    if ((_curr_room->getNeighbourPtr(id) == nullptr) || (_curr_room == nullptr)) {
        return false;
    }
    _curr_room = _curr_room->getNeighbourPtr(id);
    return true;
}

bool ActingBot::setStamina(int stamina) {
    if (_stamina != 0 || stamina <= 0) {
        return false;
    }
    _stamina = stamina;
    return true;
}

void ActingBot::addIron(int iron) {
    _collected_iron += iron;
}

void ActingBot::addGold(int gold) {
    _collected_gold += gold;
}

void ActingBot::addGems(int gems) {
    _collected_gems += gems;
}

void ActingBot::addExp(int exp) {
    _collected_exp += exp;
}

bool ActingBot::act(Action* act_ptr) {
    _stamina -= 1;
    return act_ptr->perform();
}

bool ActingBot::Go::perform() {
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
            _bt->addIron(curr_room->iron());
            curr_room->iron() = 0;
            break;
        }
        case Resource::Gold: {
            _bt->addGold(curr_room->gold());
            curr_room->gold() = 0;
            break;
        }
        case Resource::Gems: {
            _bt->addGems(curr_room->gems());
            curr_room->gems() = 0;
            break;
        }
        case Resource::Exp: {
            _bt->addExp(curr_room->exp());
            curr_room->exp() = 0;
            break;
        }
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

int ActingBot::getStamina() {
    return _stamina;
}
