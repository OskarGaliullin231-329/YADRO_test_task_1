#include "../include/Bot.h"

int Bot::getStamina() {
    return _stamina;
}

bool Bot::setStamina(int stamina) {
    if (_stamina != -1 || stamina <= 0) {
        return false;
    }
    _stamina = stamina;
    return true;
}

bool Bot::moveToRoom(int id) {
    if (!VertexManager::getInstance().exists(id)) {
        return false;
    }
    // TODO: implement logic
    return true;
}
