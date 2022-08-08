#pragma once

#include <iostream>
#include <map>

using namespace std;

class Tables
{
public:
    map<int64_t, string> tableGroupidToKeyword;
    map<int64_t, int64_t> tableUseridToGroupid;
    map<int64_t, int64_t> tableGroupidToMessageid;
};

extern Tables tables;   