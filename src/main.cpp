#include "main.h"

int main(int argc, char *argv[])
{

#ifdef _WIN32
    _mkdir(dir.c_str());
#else
    mkdir(dir.c_str(), 0777);
#endif

    input(argc, argv);
    return 0;
}

void input(int argc, char *argv[])
{
    InputParser input(argc, argv);
    Command command = Command();

    command.addCommand("run", runScript);
    command.addCommand("help", help);
    command.addDefaultCommand(runScript);
    command.runCommand(argv[1],argc, argv);
}

void runScript(int argc,char *argv[])
{

    std::cout << "Running script: " << argv[1] << std::endl;
    std::string pre_script = "cd " + dir + " && ";
    std::string script = pre_script + dir + "/" + argv[1];
    std::cout << "Running script: " << script << std::endl;
    system(script.c_str());
}

void help(int argc,char *argv[])
{
    std::cout << "Usage: autom [command] [options]" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  run [script] - Runs a script" << std::endl;
    std::cout << "  help - Shows this help message" << std::endl;
}