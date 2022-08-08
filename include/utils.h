#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

namespace AdditionalFunctions
{
    std::string Token(const std::string& path);

    int64_t GetGroupIdFromMessage(const std::string& text);
}