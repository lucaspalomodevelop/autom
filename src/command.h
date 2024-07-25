#ifndef COMMAND_H
#define COMMAND_H

#include <map>
#include <string>
#include <iostream>
#include <functional>

struct CommandInfo
{
    std::string name;
    std::string description;
    // void (*func)(int argc, char *argv[]);
    std::function<void(int argc, char *argv[])> func;
};

class Command
{
public:
    Command(void);
    ~Command(void);

    // add a command alias to the command map
    void addCommandAlias(std::string name, std::string alias);
    // add a command to the command map
    void addCommand(std::string name, std::function<void(int argc, char *argv[])> funcs);
    // void addCommand(std::string name, void (*func)(int argc, char *argv[]));
    void addCommand(std::string name, std::string description, std::function<void(int argc, char *argv[])> funcs);
    // void addCommand(std::string name, std::string description, void (*func)(int argc, char *argv[]));
    // add a default command to the command map
    // void addDefaultCommand(void (*func)(int argc, char *argv[]));
    void addDefaultCommand(std::function<void(int argc, char *argv[])> funcs);
    // run a command
    void runCommand(std::string name, int argc, char *argv[]);
    // check if a command is in the command map
    bool isInCommands(std::string name);

    std::string listCommands();

private:
    // map of commands
    std::map<std::string, CommandInfo> commands;
    // default command
    // void (*defaultCommand)(int argc, char *argv[]);
    std::function<void(int argc, char *argv[])> defaultCommand;
};

#endif // COMMAND_H