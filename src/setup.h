

#ifndef SETUP_H
#define SETUP_H

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>

#include "debug.h"
#include "../libs/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

class Setup
{
private:
public:
#ifdef _WIN32

    std::string home = getenv("USERPROFILE");
    std::string editor = "notepad.exe";
#else
    std::string home = getenv("HOME");
    std::string editor = "vim";
#endif
    Setup(/* args */)
    {
        home = home + "/.autom";

        runSetup();
    }

    ~Setup()
    {
    }

    void createFolder()
    {
#ifdef _WIN32
        DEBUG("creating folder on windows");
        _mkdir((home).c_str());
#else
        DEBUG("creating folder on linux");
        mkdir((home).c_str(), 0777);
#endif
    }

    void createSettings()
    {
        DEBUG("creating settings file");

        DEBUG("replacing backslashes with forward slashes");
        std::replace(home.begin(), home.end(), '\\', '/');

        std::ofstream file(home + "/.automconfig.json");

        DEBUG("creating settings file with default settings");
        json j = {
            {"editor", editor},
            {"search_dirs", {home}},
            {"autom_home_dir", home}};

        DEBUG("writing settings to file");
        file << j.dump(4);

        DEBUG("closing file");
        file.close();
    }

    void runSetup()
    {

        if (!std::filesystem::exists(home))
        {
            DEBUG("creating folder");
            createFolder();
        }

        if (!std::filesystem::exists(home + "/.automconfig.json"))
        {
            DEBUG("creating settings file");
            createSettings();
        }
    }
};

#endif // SETUP_H