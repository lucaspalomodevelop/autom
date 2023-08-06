#include "command.h"

Command::Command() {}

Command::~Command() {}


// add a command alias to the command map
void Command::addCommandAlias(std::string name, std::string alias)
{
    CommandInfo mycommand{
        alias,
        commands[name].description,
        commands[name].func};
    commands[alias] = mycommand;
}

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
void Command::runCommand(std::string name, int argc, char *argv[])
{
    // std::cout << "Running command: " << name << std::endl;
    if (this->isInCommands(name))
    {

        char *argv2[argc];

        for (int i = 0; i < argc; i++)
        {
            argv2[i] = argv[i + 1];
        }
        commands[name].func(argc - 1, argv2);
    }
    else
    {
        defaultCommand(argc, argv);
    }
}


// check if a command is in the command map
bool Command::isInCommands(std::string name)
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

    
    for (std::map<std::string, CommandInfo>::iterator it = commands.begin(); it != commands.end(); ++it)
    {
        list += "\t" + it->second.name + " " + it->second.description + "\n";
    }
    return list;
}