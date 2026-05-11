#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <list>
#include <string>

#include "Bot.h"
#include "Rooms.h"

template <typename T>
class Strategy {
public:
    class Action {
    public:
        virtual std::string stringify() = 0;
    };

    class Go: public Action {
    public:
        Go(int id): _id(id) {} 
        std::string stringify() override {
            std::string result("go ");
            return result + std::to_string(id);
        }
    private:
        int _id;
    }

    class Collect: public Action {
    public:
        enum class Resource {
            Iron,
            Gold,
            Gems,
            Exp
        };
        Collect(Resource resource): _resource(resource) {}
        std::string stringify() override {
            std::string result("collect ");
            switch (_resource) {
                case Resource::Iron: {
                    result += "iron";
                    break;
                }
                case Resource::Gold: {
                    result += "gold";
                    break;
                }
                case Resource::Gems: {
                    result += "gems";
                    break;
                }
                case Resource::Exp: {
                    result += "exp";
                    break;
                }
            }
            return result;
        }
    private:
        Resource _resource;
    }

    void perform() {
        static_cast<T*>(this)->perform();
    }

private:
    Bot* bot;
    std::list <Action*> _actions;
};


class AliceStrategy: Strategy<AliceStrategy> {
public:
    void perform();
private:
};

#endif // STRATEGY_H_
