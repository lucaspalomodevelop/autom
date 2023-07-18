

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
    std::ifstream file(setup.home + "/.automconfig.toml");
    if (!file.is_open())
    {
        std::cout << "Error:" + setup.home + "/.automconfig.toml not found" << std::endl;
        setup.createSettings();
        readSettings();
    }
    this->value = toml::parse(file);
}