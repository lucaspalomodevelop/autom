

#ifndef SETTINGS_H
#define SETTINGS_H

#include "debug.h"
#include "../libs/json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

#ifdef _WIN32
#include <direct.h>
#endif

#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "./setup.h"
#include "./singleton.h"

class Settings : public Singleton<Settings>
{

private:
    std::string settings_name = ".automconfig.json";

public:
    json value;
    std::string filepath;
    Settings(void);
    ~Settings(void);
    void readSettings();
    void writeSettings();
    std::string getSettingsAsString();
    Settings &operator=(const Settings &) = default;
};

#endif // SETTINGS_H