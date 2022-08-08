#include "../include/utils.h"
#include <algorithm>
#include <exception>

std::string AdditionalFunctions::Token(const std::string& path)
{
    std::ifstream file("token.txt");

    std::string token;
    if(!file.is_open()) {
        std::cout << "Could not find a token in token.txt" << std::endl;
        return " ";
    }

    file >> token;
    return token;
}

int64_t AdditionalFunctions::GetGroupIdFromMessage(const std::string& text)// UPGRADE IN FUTURE: use c++ version str to int64 
{
    int64_t groupID = 0;
    try {
        auto strGroupID = text.substr(7, text.size()); 
        groupID = strtoll(strGroupID.c_str(), NULL, 10);
    }
    catch(std::exception& e){ }

    return groupID;
}