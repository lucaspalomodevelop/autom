
#include <iostream>
#include <string>
#include <sys/stat.h>
#include "inputparser.h"
#include "command.h"

#ifdef _WIN32
#include <direct.h>
std::string home = getenv("USERPROFILE");
#else
std::string home = getenv("HOME");
#endif

std::string dir = home + "/autom";

void input(int argc, char *argv[]);
void runScript(int argc,char *argv[]);
void help(int argc,char *argv[]);
void create(int argc,char *argv[]);
void remove(int argc,char *argv[]);
void list(int argc,char *argv[]);
void edit(int argc,char *argv[]);
void run(int argc,char *argv[]);
