#include "../include/Strategy.h"

#include <map>
#include <queue>

#include "../include/Bot.h"
#include "../include/Loger.h"
#include "../include/Rooms.h"

#include "utility_funcs.h"

void AliceStrategy::setPrefResource(Resource resource) {
    _prefered_res = resource;
}

void AliceStrategy::perform(ActingBot& bot) {
    ActingBot* acting_bot = &bot;
    int start_stamina = acting_bot->getStamina();
    VertexManager* vm_ptr = &VertexManager::getInstance();
    Room* curr_room_ptr = static_cast<Room*>(vm_ptr->getVertexPtr(acting_bot->currRoomID()));
    ActingBot::Action* action;
    while (acting_bot->getStamina() < start_stamina / 2) {
        curr_room_ptr = static_cast<Room*>(curr_room_ptr->getLeastIDNeibourPtr());
        action = new ActingBot::Go(*acting_bot, curr_room_ptr->getID());
        _loger->addEvent(Event(action, *curr_room_ptr));
        acting_bot->act(action);

        action = new ActingBot::Collect(*acting_bot, max_profit_resource(curr_room_ptr, _prefered_res));
        _loger->addEvent(Event(action, *curr_room_ptr));
        acting_bot->act(action);
    }
    // TODO: модернизировать логику исследования

    std::queue<int> way_back;
    BFS_path(curr_room_ptr, 0, way_back, false);
    way_back.pop();
    while (!way_back.empty()) {
        action = new ActingBot::Go(*acting_bot, way_back.front());
        acting_bot->act(action);
        curr_room_ptr = static_cast<Room*>(vm_ptr->getVertexPtr(way_back.front()));
        _loger->addEvent(Event(action, *curr_room_ptr));
        if (acting_bot->getStamina() > way_back.size()) {
            action = new ActingBot::Collect(*acting_bot, max_profit_resource(curr_room_ptr, _prefered_res));
        }
        way_back.pop();
    }
}
