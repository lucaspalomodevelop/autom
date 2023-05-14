#include "main.h"

int main(int argc, char *argv[])
{

#ifdef _WIN32
    _mkdir(dir.c_str());
#else
    mkdir(dir.c_str(), 0777);
#endif

    input(argc, argv);
    return 0;
}

// input function for parsing arguments and creating commands and running them
void input(int argc, char *argv[])
{
    InputParser input(argc, argv);

    // std::cout << "  [script] - Runs a script if autom has not command with that name" << std::endl;
    command.addCommand("run", "[script] - Runs a script", runScript);
    command.addCommand("help", "- Shows this help message", help);
    command.addCommand("ls", "- Lists all scripts ", listScripts);
    command.addCommand("add", "[script] - Adds a script", addScript);
    command.addCommand("edit", "[script] - Edits a script", editScript);
    command.addDefaultCommand(runScript);
    command.runCommand(argv[1], argc, argv);
}

// run a script with is in the autom directory
void runScript(int argc, char *argv[])
{

    // std::cout << "Running script: " << argv[1] << std::endl;
    std::string pre_script = "cd " + dir + " && ";
    std::string script = pre_script + dir + "/" + argv[1];
    // std::cout << "Running script: " << script << std::endl;
    system(script.c_str());
}

// list all scripts in the autom directory
void listScripts(int argc, char *argv[])
{
    std::cout << "Scripts:" << std::endl;
    for (const auto &entry : std::filesystem::directory_iterator(dir))
    {
        std::string name = entry.path().filename().string();
        std::cout << "  " << name << std::endl;
    }
}

// add a script in the autom directory
void addScript(int argc, char *argv[])
{

    if (std::filesystem::exists(dir + "/" + argv[1]))
    {
        std::cout << "Script " << argv[1] << " already exists" << std::endl;
        return;
    }

    std::cout << "Adding script: " << argv[1] << std::endl;
    std::string script = dir + "/" + argv[1];
    std::ofstream file(script);

#ifdef _WIN32
    file << "@echo off" << std::endl;
    _chmod(script.c_str(), _S_IREAD | _S_IWRITE);
#else
    file << "#!/bin/bash" << std::endl;
    system(("chmod +x " + script).c_str());
#endif

    file.close();

    editScript(argv[1]);
}

// edit a script in the autom directory
void editScript(int argc, char *argv[])
{
    editScript(argv[1]);
}

void editScript(std::string name)
{
    std::string script = dir + "/" + name;
#ifdef _WIN32
    system(("notepad " + script).c_str());
#else
    system(("nano " + script).c_str());
#endif
}

// help function for showing help message
void help(int argc, char *argv[])
{
    std::cout << "Usage: autom [command] [options]" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  [script] - Runs a script if autom has not command with that name" << std::endl;
    std::cout << command.listCommands() << std::endl;
}