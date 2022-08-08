#include "../include/tipCommands.h"

vector<BotCommand::Ptr> SetupCommands()
{
    vector<BotCommand::Ptr> commands;
    BotCommand::Ptr cmdArray;

    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = "start";
    cmdArray->description = "Command for start playing the game";
    commands.push_back(cmdArray);

    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = "help";
    cmdArray->description = "General rules and informations about game and developers";
    commands.push_back(cmdArray);

    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = "tip";
    cmdArray->description = "Help players to guess the word";
    commands.push_back(cmdArray);

    return commands;
}