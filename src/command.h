#ifndef COMMAND_H
#define COMMAND_H

#include <map>
#include <string>
#include <iostream>


struct CommandInfo
{
    std::string name;
    std::string description;
    void (*func)(int argc, char *argv[]);
};

class Command
{
public:
    Command(void);
    ~Command(void);

    // add a command to the command map
    void addCommand(std::string name, void (*func)(int argc, char *argv[]));
    void addCommand(std::string name, std::string description, void (*func)(int argc, char *argv[]));
    // add a default command to the command map
    void addDefaultCommand(void (*func)(int argc, char *argv[]));
    // run a command
    void runCommand(std::string name, int argc, char *argv[]);
    // check if a command is in the command map
    bool isInCommands(std::string name);

    std::string listCommands();

private:
    // map of commands
    std::map<std::string, CommandInfo> commands;
    // default command
    void (*defaultCommand)(int argc, char *argv[]);
};

#endif // COMMAND_H