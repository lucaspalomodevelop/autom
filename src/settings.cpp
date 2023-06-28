

#include "settings.h"

 Setup setup = Setup();

Settings::Settings(void)
{
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
    settings = toml::parse(file);
}


std::string Settings::getSetting(std::string path)
{
    std::string setting = settings[path].value_or("null");
    return setting;
}