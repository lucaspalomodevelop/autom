#ifndef COMMAND_H
#define COMMAND_H

#include <map>
#include <string>
#include <iostream>

class Command
{
public:
    Command(void);
    ~Command(void);

    // add a command to the command map
    void addCommand(std::string name, void (*func)(int argc, char *argv[]));
    // add a default command to the command map
    void addDefaultCommand(void (*func)(int argc,char *argv[]));
    // run a command
    void runCommand(char *name, int argc, char *argv[]);
    // check if a command is in the command map
    bool isInCommands(char *name);

private:
    // map of commands
    std::map<std::string, void (*)(int argc,char *argv[])> commands;
    // default command
    void (*defaultCommand)(int argc,char *argv[]);
};

#endif // COMMAND_H