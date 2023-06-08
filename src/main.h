
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>

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
Command command = Command();

// input function for parsing arguments and creating commands and running them
void input(int argc, char *argv[]);
// run a script with is in the autom directory
void runScript(int argc, char *argv[]);
// list all scripts in the autom directory
void listScripts(int argc, char *argv[]);
// add a script in the autom directory
void addScript(int argc, char *argv[]);
// edit a script in the autom directory
void editScript(int argc, char *argv[]);
void editScript(std::string name);
// remove a script in the autom directory
void removeScript(int argc, char *argv[]);
// show a script in the autom directory
void showScript(int argc, char *argv[]);
// help function for showing help message
void help(int argc, char *argv[]);
// void create(int argc,char *argv[]);
// void remove(int argc,char *argv[]);
// void list(int argc,char *argv[]);
// void edit(int argc,char *argv[]);
// void run(int argc,char *argv[]);
