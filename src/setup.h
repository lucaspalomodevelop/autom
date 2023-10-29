

#ifndef SETUP_H
#define SETUP_H

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>
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
        _mkdir((home).c_str());
#else
        mkdir((home).c_str(), 0777);
#endif
    }

    void createSettings()
    {
        std::replace(home.begin(), home.end(), '\\', '/');


        std::ofstream file(home + "/.automconfig.json");

         json j = {
            {"editor", editor},
            {"search_dirs", {home}},
            {"autom_home_dir", home}
        };

        file << j.dump(4);

        file.close();

    }

    void runSetup()
    {

        if (!std::filesystem::exists(home))
            createFolder();

        if (!std::filesystem::exists(home + "/.automconfig.json"))
            createSettings();
    }
};

#endif // SETUP_H