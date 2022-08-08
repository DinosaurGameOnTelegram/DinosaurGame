#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <algorithm>
#include <type_traits>
#include <functional>
#include <map>
#include <fstream>

#include "../include/tipCommands.h"
#include "../include/commands.h"
#include "../include/keyboardForGroup.h"
#include "../include/commandsFunctionality.h"
#include "../include/utils.h"

#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

int main() {
    TgBot::Bot bot(AdditionalFunctions::Token("token.txt"));

    bot.getApi().setMyCommands(SetupCommands());

    string urlBot = "https://t.me/" + bot.getApi().getMe()->username;
    int64_t groupID = 1234;

    keyboardGroup.checkButton->text = "Choose a word";
    keyboardGroup.checkButton->url  = urlBot + "?start=" + to_string(groupID);
    // checkButton->callbackData = "check";
    
    keyboardGroup.row0.push_back(keyboardGroup.checkButton);
    keyboardGroup.keyboard->inlineKeyboard.push_back(keyboardGroup.row0);

    bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
        CommandStart(message, bot); 
    });

    bot.getEvents().onCommand("tip", [&bot](Message::Ptr message) {
        CommandTip(message, bot);
    });

    bot.getEvents().onCommand("help", [&bot](Message::Ptr message) {
        CommandHelp(message, bot);
    });

    bot.getEvents().onAnyMessage([&bot, &groupID](TgBot::Message::Ptr message) {
        AnyMessage(message, bot);
    });


    signal(SIGINT, [](int s) {
        printf("SIGINT got\n");
        exit(0);
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        bot.getApi().deleteWebhook();

        TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (exception& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}