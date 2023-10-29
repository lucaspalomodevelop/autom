

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