#include "../include/FileGraphParser.h"

#include <fstream>
#include <optional>
#include <regex>
#include <string>
#include <utility>

std::pair<int, std::string> parseResourceSafe(const std::string& input) {
    static const std::regex re(R"(^\s*(\d+)\s+([a-zA-Z]+)\s*$)");
    std::smatch m;
    if (std::regex_match(input, m, re))
        return {std::stoi(m[1]), m[2].str()};
    return {-1, ""};
}

Resource stringToResource(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    if (str == "iron")
        return Resource::Iron;
    if (str == "gold")
        return Resource::Gold;
    if (str == "gems")
        return Resource::Gems;
    if (str == "exp")
        return Resource::Exp;
    return Resource::Err;
}

bool FileGraphParser::parseFrom(std::ifstream& file) {
    bool result = true;
    VertexManager* vm_ptr = &VertexManager::getInstance();
    std::string line;
    while (getline(file, line) && result) {
        Record rec = createRecord(line);
        result = recordIsOK(rec);
        if (result == true) {
            vm_ptr->addVertex(rec._room_id, new Room(rec._room_id, rec._iron, rec._gold, rec._gems, rec._exp));
            Vertex* room = vm_ptr->getVertexPtr(rec._room_id);
            for (int id : rec._neighbours) {
                if (vm_ptr->exists(id)) {
                    room->addNeighbour(*(vm_ptr->getVertexPtr(id)));
                }
            }
        }
        else {
            std::regex end_line_regex(R"(^(\d+)\s+(gems|iron|gold|exp)$)", std::regex::icase);
            if (std::regex_match(line, end_line_regex)) {
                std::pair<int, std::string> pr = parseResourceSafe(line);
                _prefered_res = stringToResource(pr.second);
                if (_prefered_res != Resource::Err) {
                    _bot_stamina = pr.first;
                }
                else { _loger->showErrorMsg(line); }
            }
            else { _loger->showErrorMsg(line); }
        }
    }
    return result;
}
