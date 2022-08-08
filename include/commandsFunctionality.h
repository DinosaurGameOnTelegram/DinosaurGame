#pragma once

#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

void CommandHelp(Message::Ptr message, TgBot::Bot& bot);

void CommandStart(Message::Ptr message, TgBot::Bot& bot);

void CommandTip(Message::Ptr message, TgBot::Bot& bot);

void AnyMessage(Message::Ptr message, TgBot::Bot& bot);