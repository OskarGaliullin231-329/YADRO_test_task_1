#include "../include/Strategy.h"

#include <algorithm>
#include <map>

#include "Bot.h"
#include "Loger.h"
#include "Rooms.h"

void AliceStrategy::perform(ActingBot& bot) {
    ActingBot* acting_bot = &bot;

    int start_stamina = acting_bot->getStamina();
    int iron_coef = 7;
    int gold_coef = 11;
    int gems_coef = 23;
    int exp_coef  = 1;
    switch (_prefered_res) {
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
    VertexManager* vm_ptr = &VertexManager::getInstance();
    int max_profit = -1;
    Room* curr_room_ptr = static_cast<Room*>(vm_ptr->getVertexPtr(acting_bot->currRoomID()));
    ActingBot::Action* action;
    while (acting_bot->getStamina() < start_stamina / 2) {
        curr_room_ptr = static_cast<Room*>(curr_room_ptr->getLeastIDNeibourPtr());
        action = new ActingBot::Go(*acting_bot, curr_room_ptr->getID());
        _loger->addEvent(Event(action, *curr_room_ptr));
        acting_bot->act(action);
        max_profit = std::max({curr_room_ptr->iron() * iron_coef,
                               curr_room_ptr->gold() * gold_coef,
                               curr_room_ptr->gems() * gems_coef,
                               curr_room_ptr->exp() * exp_coef});
        if (curr_room_ptr->iron() * iron_coef == max_profit) {
            action = new ActingBot::Collect(*acting_bot, Resource::Iron);
        }
        else if (curr_room_ptr->gold() * gold_coef == max_profit) {
            action = new ActingBot::Collect(*acting_bot, Resource::Gold);
        }
        else if (curr_room_ptr->gold() * gems_coef == max_profit) {
            action = new ActingBot::Collect(*acting_bot, Resource::Gems);
        }
        else if (curr_room_ptr->exp() * exp_coef == max_profit) {
            action = new ActingBot::Collect(*acting_bot, Resource::Exp);
        }
        _loger->addEvent(Event(action, *curr_room_ptr));
        acting_bot->act(action);
    }
}
