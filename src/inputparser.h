#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

class InputParser
{
    std::map<std::string, std::string> args;

public:
    InputParser(int argc, char *argv[]);
    std::string getValue(std::string key);
    bool hasKey(std::string key);
};

#endif // INPUTPARSER_H