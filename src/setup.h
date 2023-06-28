

#ifndef SETUP_H
#define SETUP_H

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>

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

        std::ofstream file(home + "/.automconfig.toml");
        file << "editor = \"" << editor << "\"" << std::endl;
        file << "search_dirs = [\"" << home << "\"]" << std::endl;
        file << "autom_home_dir = \"" << home << "\"" << std::endl;

        file.close();
    }

    void runSetup()
    {
        createFolder();
        createSettings();
    }
};

#endif // SETUP_H