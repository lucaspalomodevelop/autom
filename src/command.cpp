#include "command.h"
#include <iostream>

Command::Command() {}

Command::~Command() {}

void Command::addCommand(std::string name, void (*func)(char *argv[]))
{
    commands[name] = func;
}

void Command::addDefaultCommand(void (*func)(char *argv[]))
{
    defaultCommand = func;
}

void Command::runCommand(char *name, char *argv[])
{
    std::cout << "Running command: " << name << std::endl;
    if (commands.count(name) > 0)
    {
        commands[name](argv);
    }
    else
    {
        defaultCommand(argv);
    }
}
