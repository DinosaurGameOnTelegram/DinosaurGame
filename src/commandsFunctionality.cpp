#include "../include/commandsFunctionality.h"
#include "../include/commands.h"
#include "../include/keyboardForGroup.h"
#include "../include/utils.h"
#include "../include/tables.h"
#include <tgbot/types/Chat.h>

void CommandHelp(Message::Ptr message, TgBot::Bot& bot)
{
    string response = "It is command help";
    bot.getApi().sendMessage(message->chat->id, response); // add buttons for message

    // ..
}

void CommandStart(Message::Ptr message, TgBot::Bot& bot)
{
    if(message->chat->type == TgBot::Chat::Type::Private) {
        int64_t  groupID = AdditionalFunctions::GetGroupIdFromMessage(message->text);
        
        if(groupID == 0)
        {
            CommandHelp(message, bot);
            return;
        }

        if (tables.tableGroupidToKeyword.find(groupID) != tables.tableGroupidToKeyword.end()){
            bot.getApi().sendMessage(message->chat->id, "The word is already choosed"); 
            return;
        }

        bot.getApi().sendMessage(message->chat->id, "Choose a word for encrypt");            
        tables.tableUseridToGroupid.insert({message->chat->id, groupID});        
    }  
    else if(message->chat->type == TgBot::Chat::Type::Group || message->chat->type == TgBot::Chat::Type::Supergroup) {
        if (auto d(tables.tableGroupidToMessageid.find(message->chat->id)); d != tables.tableGroupidToMessageid.end()){
            bot.getApi().deleteMessage(message->chat->id, d->second);
            tables.tableGroupidToMessageid.erase(message->chat->id);
        }
        string urlBot = "https://t.me/" + bot.getApi().getMe()->username;
        keyboardGroup.checkButton->url  = urlBot + "?start=" + to_string(message->chat->id);
        auto newMessage = bot.getApi().sendMessage(message->chat->id, "Tap to jump to bot and choose a word",
                                        false, 0, keyboardGroup.keyboard, "Markdown");
        tables.tableGroupidToMessageid.insert({message->chat->id, newMessage->messageId});
    }     
}

void CommandTip(Message::Ptr message, TgBot::Bot& bot)
{
    if(message->chat->type == TgBot::Chat::Type::Group || message->chat->type == TgBot::Chat::Type::Supergroup) {
        if(tables.tableGroupidToKeyword.find(message->chat->id) != tables.tableGroupidToKeyword.end()) {
            string word_with_stars = " "; // ****a****b**c
            string encrypt_word = tables.tableGroupidToKeyword.at(message->chat->id);
            for(size_t i = 0; i < encrypt_word.size(); ++i)
            {
                if(i % 4 == 0) // every 4th symbols
                {
                    word_with_stars += encrypt_word[i];
                    continue;
                }
                word_with_stars += '*';
            }
            bot.getApi().sendMessage(message->chat->id, "It`s word in order to help players..\n" + word_with_stars);
        }
    }     
}

void AnyMessage(Message::Ptr message, TgBot::Bot& bot)
{
    if (StringTools::startsWith(message->text, "/start")) {
            return;
        }

    if(StringTools::startsWith(message->text, "/choose_word")) {
        return;
    }

        if(StringTools::startsWith(message->text, "/help")) {
        return;
    }

        if(StringTools::startsWith(message->text, "/tip")) {
        return;
    }

    if((message->chat->type == TgBot::Chat::Type::Group) || 
        (message->chat->type == TgBot::Chat::Type::Supergroup))  {
        if(tables.tableGroupidToKeyword.find(message->chat->id) != tables.tableGroupidToKeyword.end()) {
            if(tables.tableGroupidToKeyword.at(message->chat->id) == message->text) {
            
            bot.getApi().sendMessage(message->chat->id, "You successfully guess a word;\n Congratulations!");
            bot.getApi().sendMessage(message->chat->id, "To go on a game tap /../");

            tables.tableGroupidToKeyword.erase(message->chat->id);            
            return;
            }
        }
    }

    if(message->chat->type == TgBot::Chat::Type::Private) {
        if (tables.tableUseridToGroupid.find(message->chat->id) == tables.tableUseridToGroupid.end()) {
            CommandHelp(message,bot);
            return;
        }        
        auto groupID = tables.tableUseridToGroupid.at(message->chat->id);
        tables.tableGroupidToKeyword.insert({groupID, message->text});
        tables.tableUseridToGroupid.erase(message->chat->id);

        bot.getApi().sendMessage(message->chat->id, "You successfully encrypt a word ; )");        

        auto messageIdForDelete = tables.tableGroupidToMessageid.find(groupID);
        if(messageIdForDelete == tables.tableGroupidToMessageid.end()){
            return;
        }
        bot.getApi().deleteMessage(messageIdForDelete->first, messageIdForDelete->second);
        tables.tableGroupidToMessageid.erase(groupID);
        bot.getApi().sendMessage(groupID, "The word is already choosed by @" + message->chat->username);
    }
}