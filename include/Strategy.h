#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <list>

#include "Bot.h"
#include "Loger.h"

template <typename T>
class Strategy {
public:
    Strategy() {}
    void perform(ActingBot& bot) {
        static_cast<T*>(this)->perform(bot);
    }

protected:
    Loger* _loger;
};

class AliceStrategy: Strategy<AliceStrategy> {
public:
    void setPrefResource(Resource);
    void perform(ActingBot&);

private:
    Resource _prefered_res;
};

#endif // STRATEGY_H_
