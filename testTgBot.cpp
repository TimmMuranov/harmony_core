/* 
g++ testTgBot.cpp -o bin/testTgBot --std=c++20 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread
clear
*/   
#include <stdio.h>
#include <tgbot/tgbot.h>

#include "core/core.h"

TgBot::Bot bot("7923105858:AAFPCA1cc1sacxBdUpfQP1aeWI-Rv_mTdFg");
string mode = "start";   // костыль, позволяющий определить режим работы бота
string command = "";     // костыль, хранящий команду режима
Note note;

int main(){
//-------------------------- Установка режима работы бота -----------------------------------
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        mode = "satrt";
        bot.getApi().sendMessage(message->chat->id, "Доступные режимы работы:\n/note");
    });
    bot.getEvents().onCommand("note", [&bot](TgBot::Message::Ptr message){
        mode = "note";
        bot.getApi().sendMessage(message->chat->id,
            "Режим работы с нотой акривирован. Доступные команды:\n"
            "/set - установить имя и знак ноты\n"
            "/setoctave - установить октаву ноты\n"
            "/get - получить имя ноты и ее октаву\n"
            "/exit - выйти из режима работы с нотой"
            );
    bot.getEvents().onCommand("note", [&bot](TgBot::Message::Ptr message) {
        
        bot.getApi().sendMessage(message->chat->id, "Режим ноты активирован");
    });
    bot.getEvents().onCommand("interval", [&bot](TgBot::Message::Ptr message){
        mode = "interval";
        bot.getApi().sendMessage(message->chat->id, "Режим работы с интервалом активирован");
    });
//-------------------- обработчик сообщений в зависимости от режима -------------------------
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        string userText = message->text.c_str();
        if(userText == "/start" || userText == "/note" || userText == "/interval") return;

        printf("User wrote %s\n", userText);
        
        bot.getApi().sendMessage(message->chat->id, "Вы ввели: " + userText + ".\nРежим работы: " + mode);
    });
//-----------------------------      старт      -----------------------------------
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}
//Я просто хз как сдвинуться с этой мертвой точки. Эту библиотеку определенно написало существо с другой планеты....

