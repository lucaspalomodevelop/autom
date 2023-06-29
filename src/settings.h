

#ifndef SETTINGS_H
#define SETTINGS_H

#include "../lib/toml++/toml.h"

#ifdef _WIN32
#include <direct.h>
#endif

#include "settings.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "./setup.h"

class Settings
{

private:
    toml::table settings;
    std::string settings_name = ".automconfig.toml";

public:
    Settings(void);
    ~Settings(void);
    void readSettings();
    std::string getSetting(std::string path);
};

#endif // SETTINGS_H