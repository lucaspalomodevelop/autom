

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <conio.h>

#include "inputparser.h"
#include "command.h"
#include "settings.h"

Settings settings;
// directory for autom scripts
std::string home_dir = "";
Command command;

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
void editScript(std::string name, std::string dir);
// remove a script in the autom directory
void removeScript(int argc, char *argv[]);
// show a script in the autom directory
void showScript(int argc, char *argv[]);
// encrypt a script in the autom directory
void encryptScript(int argc, char *argv[]);
// decrypt a script in the autom directory
void decryptScript(int argc, char *argv[]);

std::string EnterPassword();

// help function for showing help message
void help(int argc, char *argv[]);

#endif // MAIN_H