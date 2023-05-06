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

// input function for parsing arguments and creating commands and running them
void input(int argc, char *argv[])
{
    InputParser input(argc, argv);
    Command command = Command();

    command.addCommand("run", runScript);
    command.addCommand("help", help);
    command.addCommand("ls", listScripts);
    command.addDefaultCommand(runScript);
    command.runCommand(argv[1], argc, argv);
}

// run a script with is in the autom directory
void runScript(int argc, char *argv[])
{

    // std::cout << "Running script: " << argv[1] << std::endl;
    std::string pre_script = "cd " + dir + " && ";
    std::string script = pre_script + dir + "/" + argv[1];
    // std::cout << "Running script: " << script << std::endl;
    system(script.c_str());
}

// list all scripts in the autom directory
void listScripts(int argc, char *argv[])
{
    std::cout << "Scripts:" << std::endl;
    for (const auto &entry : std::filesystem::directory_iterator(dir))
    {
        std::string name = entry.path().filename().string();
        std::cout << "  " << name << std::endl;
    }
}

// help function for showing help message
void help(int argc, char *argv[])
{
    std::cout << "Usage: autom [command] [options]" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  [script] - Runs a script if autom has not command with that name" << std::endl;
    std::cout << "  run [script] - Runs a script" << std::endl;
    std::cout << "  help - Shows this help message" << std::endl;
}