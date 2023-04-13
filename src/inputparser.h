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
    // get the value of a key
    std::string getValue(std::string key);
    // check if a key exists
    bool hasKey(std::string key);
};

#endif // INPUTPARSER_H