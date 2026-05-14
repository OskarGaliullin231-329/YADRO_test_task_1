#ifndef UTILITY_FUNCS_H_
#define UTILITY_FUNCS_H_

#include <algorithm>
#include <queue>
#include <utility>

#include "../include/Rooms.h"
#include "../include/Bot.h"

bool BFS_path(Room* src_room, int dest_room_id, std::queue<int>& rooms_q, bool start_is_found) {
    Room* old_room_ptr = src_room;
    start_is_found = (src_room->getID() == dest_room_id);
    for (auto nb = src_room->getNeighboursIter(); (nb!= src_room->getNeighboursEnd()) && (!start_is_found); nb++) {
        Room* nb_ptr = static_cast<Room*>(nb->second);
        if (nb_ptr->visited()) {
            start_is_found = BFS_path(nb_ptr, dest_room_id, rooms_q, start_is_found);
        }
    }
    if (start_is_found) {
        rooms_q.push(src_room->getID());
    }
    return start_is_found;
}

class PairLess {
public:
    bool operator() (const std::pair<Resource, int>& l, const std::pair<Resource, int>& r) const {
        return l.second < r.second;
    }
};

Resource max_profit_resource(Room* room, Resource prefered_resource) {
    Resource result;
    int iron_coef = 7;
    int gold_coef = 11;
    int gems_coef = 23;
    int exp_coef  = 1;
    switch (prefered_resource) {
        case Resource::Iron: {
            iron_coef *= 2;
            break;
        }
        case Resource::Gold: {
            gold_coef *= 2;
            break;
        }
        case Resource::Gems: {
            gems_coef *= 2;
            break;
        }
        case Resource::Exp: {
            exp_coef *= 2;
            break;
        }
    }
    PairLess pl;
    std::pair<Resource, int> max_profit_pair = std::max<std::pair<Resource, int>>(
        {{Resource::Iron, room->iron() * iron_coef},
         {Resource::Gold, room->gold() * gold_coef},
         {Resource::Gems, room->gems() * gems_coef},
         {Resource::Exp, room->exp() * exp_coef}}, 
        pl
    );
    result = max_profit_pair.first;
    return result;
}

#endif // UTILITY_FUNCS_H_
