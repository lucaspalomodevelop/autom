

#include "settings.h"

Setup setup;

Settings::Settings(void)
{
    setup = Setup();
    readSettings();
}

Settings::~Settings(void)
{
}

void Settings::readSettings()
{
    std::ifstream file(setup.home + "/.automconfig.json");
    if (!file.is_open())
    {
        std::cout << "Error:" + setup.home + "/.automconfig.json not found" << std::endl;
        setup.createSettings();
        readSettings();
    }
    this->value = json::parse(file);
}

std::string Settings::getSettingsAsString()
{
    return this->value.dump(4);
}

// void Settings::writeSettings()
// {
//     std::ofstream file(setup.home + "/.automconfig.json");
//     file << this->value.dump(4);
//     file.close();
// }

// void Settings::set(std::string key, std::string value)
// {
//     this->value[key] = value;
//     writeSettings();
// }

// std::string Settings::get(std::string key)
// {
//     return this->value[key];
// }

// void Settings::set(std::string key, int value)
// {
//     this->value[key] = value;
//     writeSettings();
// }
