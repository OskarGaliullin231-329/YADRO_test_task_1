#ifndef BOT_H_ 
#define BOT_H_

#include <map>
#include <string>

#include "Rooms.h"

class Bot {
public:
    Bot();
    int currRoomID();
    bool moveToRoom(int);
    bool seenRoom(int);
    Vertex* getLeastIDSeenRoom();

protected:
    Vertex* _curr_room = nullptr;
    std::map<int, Vertex*> _visible_rooms_ptrs;
};


enum class Resource {
    Iron,
    Gold,
    Gems,
    Exp
};

class ActingBot: public Bot {
public:
    friend class Action;
    class Action {
    public:
        virtual char getType() = 0;
        virtual bool perform() = 0;
        virtual std::string stringify() = 0;
    protected:
        Action(ActingBot& bt) { _bt = &bt; }
        ActingBot* _bt;
    };
    class Go: public Action {
    public:
        Go(ActingBot& bt, int id): Action(bt), _id(id) {} 
        char getType() override { return 'g'; }
        bool perform() override;
        std::string stringify() override;
    private:
        int _id;
    };
    class Collect: public Action {
    public:
        Collect(ActingBot& bt, Resource resource): Action(bt), _resource(resource) {}
        char getType() override { return 'c'; }
        bool perform() override;
        std::string stringify() override;
    private:
        Resource _resource;
    };

    ActingBot(): Bot() {}
    bool setStamina(int);
    int getStamina() { return _stamina; }
    int getIron()    { return _collected_iron; }
    int getGold()    { return _collected_gold; }
    int getGems()    { return _collected_gems; }
    int getExp()     { return _collected_exp; }

    bool act(Action*);

private:
    int _stamina = 0;
    int _collected_iron = 0;
    int _collected_gold = 0;
    int _collected_gems = 0;
    int _collected_exp  = 0;
};

#endif // BOT_H_
