
#include <iostream>
#include <string>
#include <sys/stat.h>
#include "inputparser.h"
#include "command.h"

std::string home = getenv("HOME");
std::string dir = home + "/autom";

void input(int argc, char *argv[]);
void runScript(char *argv[]);
void help(char *argv[]);
void create(char *argv[]);
void remove(char *argv[]);
void list(char *argv[]);
void edit(char *argv[]);
void run(char *argv[]);
