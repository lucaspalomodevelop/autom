

#ifndef SETTINGS_H
#define SETTINGS_H

#include "../lib/toml/toml.hpp"

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
    std::string settings_name = ".automconfig.toml";
    toml::value value;

public:
    Settings(void);
    ~Settings(void);
    void readSettings();
    Settings &operator=(const Settings &) = default;

template <typename T>
T getSetting(std::string path)
{
    T setting = toml::find<T>(value, path);
    return setting;
}
};

#endif // SETTINGS_H