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
    void addCommand(std::string name, void (*func)(int argc, char *argv[]));
    void addDefaultCommand(void (*func)(int argc,char *argv[]));
    void runCommand(char *name, int argc, char *argv[]);
    bool isInCommands(char *name);

private:
    std::map<std::string, void (*)(int argc,char *argv[])> commands;
    void (*defaultCommand)(int argc,char *argv[]);
};

#endif // COMMAND_H