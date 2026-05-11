#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <list>

#include "Bot.h"
#include "Rooms.h"

template <typename T>
class Strategy {
public:
    void perform() {
        static_cast<T*>(this)->perform();
    }

protected:
    ActingBot* bot;
    std::list <ActingBot::Action*> _actions;
};

class AliceStrategy: Strategy<AliceStrategy> {
public:
    void perform();
};

#endif // STRATEGY_H_
