
#include <iostream>
#include <string>
#include <sys/stat.h>
#include "inputparser.h"
#include "command.h"

// directory for autom scripts
#ifdef _WIN32
#include <direct.h>
std::string home = getenv("USERPROFILE");
#else
std::string home = getenv("HOME");
#endif

// directory for autom scripts
std::string dir = home + "/autom";

// input function for parsing arguments and creating commands and running them
void input(int argc, char *argv[]);
// run a script with is in the autom directory
void runScript(int argc,char *argv[]);
// help function for showing help message
void help(int argc,char *argv[]);
// void create(int argc,char *argv[]);
// void remove(int argc,char *argv[]);
// void list(int argc,char *argv[]);
// void edit(int argc,char *argv[]);
// void run(int argc,char *argv[]);
