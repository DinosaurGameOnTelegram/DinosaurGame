#pragma once

#include <tgbot/tgbot.h>
#include <memory>

using namespace std;
using namespace TgBot;

class AKeyboardGroup
{
public:
    InlineKeyboardMarkup::Ptr keyboard;
    vector<InlineKeyboardButton::Ptr> row0;
    InlineKeyboardButton::Ptr checkButton;

    AKeyboardGroup() {
        keyboard = make_shared<InlineKeyboardMarkup>();
        checkButton = make_shared<InlineKeyboardButton>();
    }

    void KeyboardSetupButton() {

    }
};



extern AKeyboardGroup keyboardGroup;