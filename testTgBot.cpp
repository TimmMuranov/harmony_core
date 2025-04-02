/* 
g++ testTgBot.cpp -o bin/testTgBot --std=c++20 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread
clear
*/ 
#include <iostream>
#include <tgbot/tgbot.h>
#include "core/core.h"
using namespace std;
using namespace TgBot;

Bot bot("token");

boost::variant< std::int64_t, std::string > workChat; // айди рабочего чата
Message::Ptr workMessage; // данные сообщения-монитора
Message::Ptr keyMessage; // данные сообщения-клавиатуры
string workMode = "none"; // запущенный режим работы

string getWorkMessage(Note note){
    return 
    "Данные ноты:\n"
    "Имя: " + (string)note.getName();
}

int enChngFlag = 0; // для энгармонической замены
Note note;

int main() {
    bot.getEvents().onCommand("start", [&bot](Message::Ptr message){
        bot.getApi().sendMessage(message->chat->id, "Прив ^^");
        workChat = message->chat->id;
    });
    bot.getEvents().onCommand("note", [&bot](Message::Ptr message) {
        workChat = message->chat->id; // сохраняем идентификатор чата
        workMode = "note";
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup); // cсоздаем доп. клавиатуру

        InlineKeyboardButton::Ptr exitBtn(new InlineKeyboardButton);  // создаем кнопки
        exitBtn->text = "Завершить работу";
        exitBtn->callbackData = "exit";

        InlineKeyboardButton::Ptr upBut(new InlineKeyboardButton);
        upBut->text = "Повысить";
        upBut->callbackData = "up";

        InlineKeyboardButton::Ptr downBut(new InlineKeyboardButton);
        downBut->text = "Понизить";
        downBut->callbackData = "down";
        
        InlineKeyboardButton::Ptr enharmonyChng(new InlineKeyboardButton);
        enharmonyChng->text = "Энгармоническая замена";
        enharmonyChng->callbackData = "enChng";

        vector<vector<InlineKeyboardButton::Ptr>> rows;
        rows.push_back({exitBtn}); // Первый ряд с одной кнопкой
        rows.push_back({upBut, downBut}); // Второй ряд с двумя кнопками
        rows.push_back({enharmonyChng});

        keyboard->inlineKeyboard = rows;

        LinkPreviewOptions::Ptr ptr;
        workMessage = bot.getApi().sendMessage(message->chat->id, "...");
        keyMessage = bot.getApi().sendMessage(message->chat->id, "Нажимай на кнопки и изменяй сообщение с данными сверху", ptr, 0, keyboard);
    });

    bot.getEvents().onCallbackQuery([&bot](CallbackQuery::Ptr query) {
        string data = query->data;
        if(workMode == "note"){
            if (data == "exit") {
                bot.getApi().deleteMessage(workChat, keyMessage->messageId);
                bot.getApi().sendMessage(workChat, "Работа завершена.");
            } else if(data == "up") {
                ++note.sygn;
                if(note.name == 'b' || note.name == 'e' || note.sygn >= 2){
                    note.enharmonyChange(1);
                }
                bot.getApi().editMessageText(getWorkMessage(note), workChat, workMessage->messageId);
            } else if(data == "down") {
                --note.sygn;
                if(note.name == 'c' || note.name == 'f' || note.sygn <=-2){
                    note.enharmonyChange(0);
                }
                if(!note.octave){
                    note.octave = 1;
                    note.name = 'a';
                }
                if(getWorkMessage(note) != workMessage->text){
                    bot.getApi().editMessageText(getWorkMessage(note), workChat, workMessage->messageId);
                }
            } else if(data == "enChngUp"){
                //дописать
            } else if(data == "enChngDown"){
                //и это тоже
            }
        } else if(workMode == "interval"){
            bot.getApi().sendMessage(workChat, "Интервалы пока не работают");
        }
    });

    try {
        TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
            cout << "LP started\n";
        }
    } catch (exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
