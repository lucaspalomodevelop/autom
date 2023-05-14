#include "command.h"

Command::Command() {}

Command::~Command() {}

// add a command to the command map
void Command::addCommand(std::string name, void (*func)(int argc, char *argv[]))
{
    CommandInfo mycommand{
        name,
        "",
        func};
    commands[name] = mycommand;
}

void Command::addCommand(std::string name, std::string description, void (*func)(int argc, char *argv[]))
{
    CommandInfo mycommand{
        name,
        description,
        func};
    commands[name] = mycommand;
}

// add a default command to the command map
void Command::addDefaultCommand(void (*func)(int argc, char *argv[]))
{
    defaultCommand = func;
}

// run a command
void Command::runCommand(char *name, int argc, char *argv[])
{
    // std::cout << "Running command: " << name << std::endl;
    if (this->isInCommands(name))
    {

        for (int i = 0; i < argc; i++)
        {
            argv[i] = argv[i + 1];
        }

        commands[name].func(argc, argv);
    }
    else
    {
        defaultCommand(argc, argv);
    }
}

// check if a command is in the command map
bool Command::isInCommands(char *name)
{
    for (auto const &command : commands)
    {
        if (command.first == name)
        {
            // std::cout << "Command found: " << command.first << std::endl;
            return true;
        }
    }
    // std::cout << "Command not found: " << name << std::endl;
    return false;
}

std::string Command::listCommands()
{
    std::string list = "";
    for (auto const &command : commands)
    {
        list += "\t" + command.second.name + " " + command.second.description + "\n";
    }
    return list;
}