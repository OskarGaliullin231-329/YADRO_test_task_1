#include <fstream>
#include <iostream>

#include "include/Bot.h"
#include "include/FileGraphParser.h"
#include "include/FileLoger.h"
#include "include/Rooms.h"
#include "include/Strategy.h"

int main() {
    FileLoger file_loger = FileLoger("result.txt");
    FileGraphParser fgp = FileGraphParser(&file_loger);
    std::ifstream in_file;
    fgp.parseFrom(in_file);
    AliceStrategy alice_strategy;
    alice_strategy.setPrefResource(fgp.getPreferedResource());
    ActingBot bot;
    bot.setStamina(fgp.getBotStamina());
    alice_strategy.perform(bot);
    return 0;
}

// g++ -I include src/Vertex.cpp src/Rooms.cpp src/Bot.cpp src/Loger.cpp src/FileLoger.cpp src/FileGraphParser.cpp src/Strategy.cpp main.cpp -o bin/main
