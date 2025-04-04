/* 
g++ testTgBot.cpp -o bin/testTgBot --std=c++20 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread
clear
*/ 
#include <iostream>
#include <string>
#include <vector>
#include <tgbot/tgbot.h>
#include <ctime>
#include "core/core.h"
using namespace std;
using namespace TgBot;

Bot bot("token");

boost::variant< std::int64_t, std::string > workChat; // айди рабочего чата
Message::Ptr workMessage; // данные сообщения-монитора
Message::Ptr keyMessage; // данные сообщения-клавиатуры
string workMode = "none"; // запущенный режим работы
string workMessageData; // для контроля изменений в сообщении
Note note;
vector <Note> noteVector; //для сохранения нот
Interval interval;
Scale scale;
Key key;
string timeToWork; // для контроля отключения процесса

string getWorkMessage(Note note){
    return
    "Данные ноты:\n"
    "Имя: " + (string)note.getName() +
    "\nОктава: " + to_string(note.octave);
}

int main() {
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    timeToWork = (string)asctime(timeinfo);

    bot.getEvents().onCommand("start", [&bot](Message::Ptr message){
        bot.getApi().sendMessage(message->chat->id,
            "Прив ^^\nВремя начала работы: " + timeToWork +
            "\nСписок комманд:\n/start - выводит это меню\n"
            "/note - работа с нотой\n"
            "/interval - работа с интервалом\n"
            "/scale - работа со звукорядом\n"
            "/key - работа с тональностью");
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
        
        InlineKeyboardButton::Ptr enharmonyChngUp(new InlineKeyboardButton);
        enharmonyChngUp->text = "Энг. замена вверх";
        enharmonyChngUp->callbackData = "enChngUp";

        InlineKeyboardButton::Ptr enharmonyChngDown(new InlineKeyboardButton);
        enharmonyChngDown->text = "Энг. замена вниз";
        enharmonyChngDown->callbackData = "enChngDown";

        vector<vector<InlineKeyboardButton::Ptr>> rows;
        rows.push_back({exitBtn}); // Первый ряд с одной кнопкой
        rows.push_back({upBut, downBut}); // Второй ряд с двумя кнопками
        rows.push_back({enharmonyChngUp, enharmonyChngDown});

        keyboard->inlineKeyboard = rows;

        LinkPreviewOptions::Ptr ptr;
        workMessage = bot.getApi().sendMessage(message->chat->id, getWorkMessage(note));
        keyMessage = bot.getApi().sendMessage(message->chat->id, "Нажимай на кнопки и изменяй сообщение с данными сверху", ptr, 0, keyboard);
    });

    bot.getEvents().onCommand("note", [&bot](Message::Ptr message){
        workMode = "interval";
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
                workMessageData = getWorkMessage(note);
            } else if(data == "down") {
                --note.sygn;
                if(note.name == 'c' || note.name == 'f' || note.sygn <=-2){
                    note.enharmonyChange(0);
                }
                if(!note.octave){
                    note.octave = 1;
                    note.name = 'a';
                }
                if(getWorkMessage(note) != workMessageData){
                    bot.getApi().editMessageText(getWorkMessage(note), workChat, workMessage->messageId);
                    workMessageData = getWorkMessage(note);
                }
            } else if(data == "enChngUp"){
                note.enharmonyChange(1);
                if(getWorkMessage(note) != workMessageData){
                    bot.getApi().editMessageText(getWorkMessage(note), workChat, workMessage->messageId);
                    workMessageData = getWorkMessage(note);
                }
            } else if(data == "enChngDown"){
                note.enharmonyChange(0);
                if(getWorkMessage(note) != workMessageData){
                    bot.getApi().editMessageText(getWorkMessage(note), workChat, workMessage->messageId);
                    workMessageData = getWorkMessage(note);
                }
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
