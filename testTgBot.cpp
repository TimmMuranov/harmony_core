/* 
g++ testTgBot.cpp -o bin/testTgBot --std=c++20 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread
clear
*/ 
#include <iostream>
#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

Bot bot("7923105858:AAFPCA1cc1sacxBdUpfQP1aeWI-Rv_mTdFg");

boost::variant< std::int64_t, std::string > workChat; // хранит айди рабочего чата
Message::Ptr workMessage; // хранит данные сообщения-монитора
Message::Ptr keyMessage; // хранит данные сообщения-клавиатуры

int main() {
    bot.getEvents().onCommand("start", [&bot](Message::Ptr message){
        bot.getApi().sendMessage(message->chat->id, "Прив ^^");
        workChat = message->chat->id;
    });
    bot.getEvents().onCommand("note", [&bot](Message::Ptr message) {
        workChat = message->chat->id; // сохраняем идентификатор чата
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup); // cсоздаем доп. клавиатуру

        InlineKeyboardButton::Ptr button1(new InlineKeyboardButton);  // создаем кнопки
        button1->text = "Завершить работу";
        button1->callbackData = "but1";

        InlineKeyboardButton::Ptr button2(new InlineKeyboardButton);
        button2->text = "Кнопка 2";
        button2->callbackData = "but2";

        InlineKeyboardButton::Ptr button3(new InlineKeyboardButton);
        button3->text = "Кнопка 3";
        button3->callbackData = "but3";

        vector<vector<InlineKeyboardButton::Ptr>> rows;
        rows.push_back({ button1});   // Первый ряд с одной кнопкой
        rows.push_back({ button2, button3 });  // Второй ряд с двумя кнопками

        keyboard->inlineKeyboard = rows;

        LinkPreviewOptions::Ptr ptr;
        workMessage = bot.getApi().sendMessage(message->chat->id, "...");
        keyMessage = bot.getApi().sendMessage(message->chat->id, "Нажимай на кнопки и изменяй сообщение с данными сверху", ptr, 0, keyboard);
    });

    bot.getEvents().onCallbackQuery([&bot](CallbackQuery::Ptr query) {
        string data = query->data;
        if (data == "but1") {
            bot.getApi().deleteMessage(workChat, keyMessage->messageId);
            bot.getApi().sendMessage(workChat, "Работа завершена.");
        } else if (data == "but2") {
            bot.getApi().editMessageText("Вы нажали вторую кнопку", workChat, workMessage->messageId);
        } else if (data == "but3") {
            bot.getApi().editMessageText("Третья кнопка нажата", workChat, workMessage->messageId);
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
