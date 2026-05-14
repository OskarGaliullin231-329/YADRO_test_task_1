#ifndef LOGER_H_
#define LOGER_H_

#include <list>
#include <string>

#include "Bot.h"

class Event {
public:
    Event(ActingBot::Action* action, Room& room): _bot_action(action), _room_snapshot(room) {}
    ~Event();
    std::string stringify() const;

private:
    class RoomSnapshot {
    public:
        RoomSnapshot(Room&);
        int _id;
        int _iron;
        int _gold;
        int _gems;
        int _exp;
    };
    ActingBot::Action* _bot_action = nullptr;
    RoomSnapshot _room_snapshot;
};

class Loger {
public:
    Loger() {}
    void addEvent(const Event& event) { _event_list.push_back(event); }
    auto eventListStart() { return _event_list.begin(); }
    auto eventListEnd() { return _event_list.end(); }
    virtual void showErrorMsg(std::string&) = 0;

protected:
    ActingBot* _bot;
    std::list <Event> _event_list;
};

#endif // LOGER_H_
