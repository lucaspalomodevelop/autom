

#ifndef SETUP_H
#define SETUP_H

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <vector>

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

    std::vector<std::string> folders_to_create;

    Setup(/* args */)
    {
        home = home + "/.autom";

        folders_to_create = {home, home + "/temp"};
        runSetup();
    }

    ~Setup()
    {
    }

    void createFolder()
    {
#ifdef _WIN32
        for (std::string folder : folders_to_create)
        {
            if (!std::filesystem::exists(folder))
                _mkdir(folder.c_str());
        }
#else
        for (std::string folder : folders_to_create)
        {
            if (!std::filesystem::exists(folder))
            {
                mkdir(folder.c_str(), 0777);
            }
        }
#endif
    }

    void createSettings()
    {
        std::replace(home.begin(), home.end(), '\\', '/');

        std::ofstream file(home + "/.automconfig.json");

        json j = {
            {"editor", editor},
            {"search_dirs", {home}},
            {"temp_dir", home + "/temp"},
            {"autom_home_dir", home},
            {"cron_file", home + "/cron.txt"},
            {"scripts", {}}};

        file << j.dump(4);

        file.close();
    }

    void runSetup()
    {
        createFolder();

        if (!std::filesystem::exists(home + "/.automconfig.json"))
            createSettings();
    }
};

#endif // SETUP_H