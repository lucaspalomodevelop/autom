#include "command.h"

Command::Command() {}

Command::~Command() {}

// add a command alias to the command map
void Command::addCommandAlias(std::string name, std::string alias)
{
    DEBUG("Adding command alias: " + alias + " for command: " + name);
    CommandInfo mycommand{
        alias,
        commands[name].description,
        commands[name].func};
    commands[alias] = mycommand;
}

// add a command to the command map
void Command::addCommand(std::string name, void (*func)(int argc, char *argv[]))
{
    DEBUG("Adding command: " + name);
    CommandInfo mycommand{
        name,
        "",
        func};
    commands[name] = mycommand;
}

void Command::addCommand(std::string name, std::string description, void (*func)(int argc, char *argv[]))
{
    DEBUG("Adding command: " + name);
    CommandInfo mycommand{
        name,
        description,
        func};
    commands[name] = mycommand;
}

// add a default command to the command map
void Command::addDefaultCommand(void (*func)(int argc, char *argv[]))
{
    DEBUG("Adding default command");
    defaultCommand = func;
}

// run a command
void Command::runCommand(std::string name, int argc, char *argv[])
{
    DEBUG("Running command: " + name);
    if (this->isInCommands(name))
    {
        DEBUG("Command found: " + name);

        char *argv2[argc];

        for (int i = 0; i < argc; i++)
        {
            DEBUG("argv[" + std::to_string(i) + "]: " + argv[i]);
            argv2[i] = argv[i + 1];
        }

        DEBUG("argc: " + std::to_string(argc));
        commands[name].func(argc - 1, argv2);
    }
    else
    {
        DEBUG("Command not found: " + name);
        DEBUG("Running default command");
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
            DEBUG("Command found: " + command.first);
            return true;
        }
    }
    DEBUG("Command not found: " + name);
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