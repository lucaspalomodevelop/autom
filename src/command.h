#ifndef COMMAND_H
#define COMMAND_H

#include <map>
#include <string>

class Command
{
public:
    Command(void);
    ~Command(void);
    void addCommand(std::string name, void (*func)(char *argv[]));
    void addDefaultCommand(void (*func)(char *argv[]));
    void runCommand(char *name, char *argv[]);

private:
    std::map<std::string, void (*)(char *argv[])> commands;
    void (*defaultCommand)(char *argv[]);
};

#endif // COMMAND_H