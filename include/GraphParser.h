#ifndef GRAPHPARSER_H_
#define GRAPHPARSER_H_

#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <list>

#include "Loger.h"
#include "Rooms.h"

template <typename T>
class GraphParser {
public:
    GraphParser(Loger* loger) { _loger = loger; }
    bool parseFrom(std::istream& stream) {
        return static_cast<T*>(this)->parseFrom(stream);
    }

    Resource getPreferedResource() {
        return _prefered_res;
    }

    int getBotStamina() {
        return _bot_stamina;
    }

protected:
    struct Record {
        int _room_id;
        int _iron;
        int _gold;
        int _gems;
        int _exp;
        std::vector<int> _neighbours;
    };

    Record createRecord(const std::string& str) const {
        Record result(-1, -1, -1, -1, -1);
        std::regex corr_rec_regex(R"(^(\d+)\s+((?:\d+(?:,\d+)*)?)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s*$)");
        std::smatch matches;
        if (std::regex_match(str, matches, corr_rec_regex)) {
            std::string neighbours_str = matches[2];
            if (!neighbours_str.empty()) {
                std::stringstream ss;
                std::string token;
                while (std::getline(ss, token, ',')) {
                    if (!token.empty()) {
                        result._neighbours.push_back(std::stoi(token));
                    }
                }
            }
            result._room_id = std::stoi(matches[1]);
            result._iron = std::stoi(matches[3]);
            result._gold = std::stoi(matches[4]);
            result._gems = std::stoi(matches[5]);
            result._exp = std::stoi(matches[6]);
        }
        return result;
    }

    bool recordIsOK(const Record& rec) {
        return (rec._room_id >= 0) && (rec._iron >= 0) && (rec._gold >= 0) && (rec._gems >= 0) && (rec._exp >= 0) && (!rec._neighbours.empty());
    }

    int _bot_stamina = -1;
    Loger* _loger = nullptr;
    Resource _prefered_res;
    std::list<Record> _records;
};

#endif // GRAPHPARSER_H_
