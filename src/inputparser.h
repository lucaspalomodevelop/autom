#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


class InputParser
{
 std::map<std::string, std::string> args;
    public:
    InputParser(int argc, char *argv[]) {
        for (int i = 1; i < argc; i++) {
            std::string arg(argv[i]);
            if (arg.find("-") == 0) {
                std::string key = arg.substr(1);
                if (i + 1 < argc) {
                    std::string value(argv[i + 1]);
                    if (value.find("-") != 0) {
                        args[key] = value;
                        i++;
                    } else {
                        args[key] = "";
                    }
                } else {
                    args[key] = "";
                }
            }
        }
    }
    std::string getValue(std::string key) {
        return args[key];
    }
    bool hasKey(std::string key) {
        return args.count(key) > 0;
    }
};
