#include "../include/FileLoger.h"

bool FileLoger::write(std::ofstream& file) {
    if (!file.good()) {
        return false;
    }
    for (auto event : _event_list) {
        file << event.stringify();
    }
    file << "result ";
    file << _bot->getIron() << ' ' << _bot->getGold() << ' ' << _bot->getGems() << ' '<< _bot->getExp() << '\n';
    return true;
}
