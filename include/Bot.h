#ifndef BOT_H_ 
#define BOT_H_

#include <string>
#include <vector>

#include "Rooms.h"

class Bot {
public:
    Bot(int);
    int currRoomID();
    bool moveToRoom(int);

private:
    Vertex* _curr_room = nullptr;
    std::vector<Vertex*> _known_rooms;
};


class ActingBot: public Bot {
public:
    class Action {
    public:
        virtual bool perform() = 0;
        virtual std::string stringify() = 0;
    protected:
        Action(ActingBot* bt) { _bt = bt; }
        ActingBot* _bt;
    };
    class Go: public Action {
    public:
        Go(ActingBot* bt, int id): Action(bt), _id(id) {} 
        bool perform() override;
        std::string stringify() override;
    private:
        int _id;
    };
    class Collect: public Action {
    public:
        enum class Resource {
            Iron,
            Gold,
            Gems,
            Exp
        };
        Collect(ActingBot* bt, Resource resource): Action(bt), _resource(resource) {}
        bool perform() override;
        std::string stringify() override;
    private:
        Resource _resource;
    };

    int getStamina();
    bool setStamina(int);
    void addIron(int);
    void addGold(int);
    void addGems(int);
    void addExp(int);

    bool act(Action*);

private:
    int _stamina = 0;
    int _collected_iron = 0;
    int _collected_gold = 0;
    int _collected_gems = 0;
    int _collected_exp  = 0;
};

#endif // BOT_H_
