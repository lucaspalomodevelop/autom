#include "command.h"
#include <iostream>

Command::Command() {}

Command::~Command() {}

void Command::addCommand(std::string name, void (*func)(int argc, char *argv[]))
{
    commands[name] = func;
}

void Command::addDefaultCommand(void (*func)(int argc, char *argv[]))
{
    defaultCommand = func;
}

void Command::runCommand(char *name, int argc, char *argv[])
{
    std::cout << "Running command: " << name << std::endl;
    if (this->isInCommands(name))
    {

        for (int i = 0; i < argc; i++)
        {
            argv[i] = argv[i + 1];
        }

        commands[name](argc, argv);
    }
    else
    {
        defaultCommand(argc, argv);
    }
}

bool Command::isInCommands(char *name)
{
    for (auto const &command : commands)
    {
        if (command.first == name)
        {
            std::cout << "Command found: " << command.first << std::endl;
            return true;
        }
    }
    std::cout << "Command not found: " << name << std::endl;
    return false;
}