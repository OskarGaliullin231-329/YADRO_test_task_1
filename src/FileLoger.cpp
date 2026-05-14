#include "../include/FileLoger.h"

FileLoger::FileLoger(std::string file_name) {
    file.open(file_name);
}

bool FileLoger::write() {
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

void FileLoger::showErrorMsg(std::string& er_msg) {
    file << er_msg;
}
