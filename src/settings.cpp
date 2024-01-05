

#include "settings.h"

Setup setup;

Settings::Settings(void)
{
    setup = Setup();
    filepath = setup.home + "/.automconfig.json";
    readSettings();
}

Settings::~Settings(void)
{
}

void Settings::readSettings()
{
    DEBUG("Reading settings");
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        DEBUG("Settings file not found");
        std::cout << "Error:" + setup.home + "/.automconfig.json not found" << std::endl;

        DEBUG("Creating settings");
        setup.createSettings();

        DEBUG("Reading settings");
        readSettings();
    }

    DEBUG("Parsing settings");
    this->value = json::parse(file);
}

std::string Settings::getSettingsAsString()
{
    DEBUG("Getting settings as string");
    return this->value.dump(4);
}

void Settings::writeSettings()
{
    DEBUG("Writing settings");
    std::ofstream file(setup.home + "/.automconfig.json");

    DEBUG("Writing settings to file");
    file << this->value.dump(4);

    DEBUG("Closing file");
    file.close();
}

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
