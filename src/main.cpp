#include "main.h"

int main(int argc, char *argv[])
{

    Settings &settings = Settings::Instance();
    command = Command();

    dir = settings.getSetting<std::string>("autom_home_dir");

    input(argc, argv);
    return 0;
}

// input function for parsing arguments and creating commands and running them
void input(int argc, char *argv[])
{
    InputParser input(argc, argv);

    // std::cout << "  [script] - Runs a script if autom has not command with that name" << std::endl;
    command.addCommand("run", "[script] - Runs a script", runScript);
    command.addCommand("help", "- Shows this help message", help);
    command.addCommand("ls", "- Lists all scripts ", listScripts);
    // command.addCommand("config", "open configure dialog", removeScript);
    command.addCommand("add", "[script] - Adds a script", addScript);
    command.addCommand("new", "[script] - Adds a script", addScript);
    command.addCommand("edit", "[script] - Edits a script", editScript);
    command.addCommand("remove", "[script] - Remove a script", removeScript);
    command.addCommand("show", "[script] - Shows a script", showScript);
    command.addDefaultCommand(runScript);
    command.runCommand(argv[1], argc, argv);
}

// run a script with is in the autom directory
void runScript(int argc, char *argv[])
{

    // std::cout << "Running script: " << argv[1] << std::endl;

    for (auto search_dir : settings.getSetting<std::vector<std::string>>("search_dirs"))
    {
        std::string script = search_dir + "/" + argv[1];
        if (std::filesystem::exists(script))
        {
            std::string pre_script = "cd " + search_dir + " && ";
            std::string args = "";
            for (int i = 2; i < argc; i++)
            {
                args += argv[i];
                args += " ";
            }
            std::string script = pre_script + search_dir + "/" + argv[1] + " " + args;
            std::cout << "executing: " << (search_dir + "/" + argv[1] + " " + args) << std::endl;
            system(script.c_str());
            return;
        }
    }
}

void showScript(int argc, char *argv[])
{

    std::map<int, std::string> dir_options;
    for (auto search_dir : settings.getSetting<std::vector<std::string>>("search_dirs"))
    {
        if (std::filesystem::exists(search_dir + "/" + argv[1]))
        {
            dir_options[dir_options.size()] = search_dir;
        }
    }

    if (dir_options.size() == 0)
    {
        std::cout << "Script " << argv[1] << " does not exist" << std::endl;
        return;
    }

    if (dir_options.size() == 1)
    {
        dir = dir_options[0];
    }

    if (dir_options.size() > 1)
    {
        std::cout << "Which script do you want to show?" << std::endl;
        for (auto &option : dir_options)
        {
            std::cout << option.first << " " << option.second << std::endl;
        }
        std::cout << "Enter number: ";
        int num;
        std::cin >> num;
        dir = dir_options[num];
    }

    std::string script = dir + "/" + argv[1];
    std::cout << "Showing script: " << script << std::endl;
    if (std::filesystem::exists(script))
    {
        std::cout << "Showing script: " << argv[1] << std::endl;
        std::ifstream file(script);
        std::string line;
        int line_number = 0;
        while (getline(file, line))
        {
            line_number++;
            std::cout << line_number << " " << line << std::endl;
        }
    }
    else
    {
        std::cout << "Script " << argv[1] << " does not exist" << std::endl;
    }
}

// list all scripts in the autom directory
void listScripts(int argc, char *argv[])
{

    std::vector<std::string> search_dirs = settings.getSetting<std::vector<std::string>>("search_dirs");

    for (auto &search_dir : search_dirs)
    {
        std::cout << "Scripts (" << search_dir << "):" << std::endl;
        for (const auto &entry : std::filesystem::directory_iterator(search_dir))
        {
            if (entry.path().filename().string().substr(0, 1) == ".")
                continue;
            if (entry.is_directory())
                continue;
            std::string name = entry.path().filename().string();
            std::cout << "  " << name << std::endl;
        }
    }
}

// add a script in the autom directory
void addScript(int argc, char *argv[])
{
    std::string add_dir = dir;

    if (settings.getSetting<std::vector<std::string>>("search_dirs").size() > 1)
    {
        std::cout << "Which directory do you want to add the script to?" << std::endl;
        std::vector<std::string> search_dirs = settings.getSetting<std::vector<std::string>>("search_dirs");
        for (int i = 0; i < search_dirs.size(); i++)
        {
            std::cout << i << " " << search_dirs[i] << std::endl;
        }
        std::cout << "Enter number: ";
        int num;
        std::cin >> num;
        add_dir = search_dirs[num];
    }

    if (std::filesystem::exists(add_dir + "/" + argv[1]))
    {
        std::cout << "Script " << argv[1] << " in folder " << add_dir << " already exists" << std::endl;
        return;
    }

    std::cout << "Adding script: " << argv[1] << std::endl;
    std::string script = add_dir + "/" + argv[1];
    std::ofstream file(script);

#ifdef _WIN32
    file << "@echo off" << std::endl;
    _chmod(script.c_str(), _S_IREAD | _S_IWRITE);
#else
    file << "#!/bin/bash" << std::endl;
    system(("chmod +x " + script).c_str());
#endif

    file.close();

    editScript(argv[1], add_dir);
}

// edit a script in the autom directory
void editScript(int argc, char *argv[])
{

    std::map<int, std::string> dir_options;

    for (auto search_dir : settings.getSetting<std::vector<std::string>>("search_dirs"))
    {
        if (std::filesystem::exists(search_dir + "/" + argv[1]))
        {
            dir_options[dir_options.size()] = search_dir;
        }
    }

    if (dir_options.size() == 0)
    {
        std::cout << "Script " << argv[1] << " does not exist" << std::endl;
        return;
    }

    if (dir_options.size() == 1)
    {
        dir = dir_options[0];
    }

    if (dir_options.size() > 1)
    {
        std::cout << "Which script do you want to edit?" << std::endl;
        for (auto &option : dir_options)
        {
            std::cout << option.first << " " << option.second << std::endl;
        }
        std::cout << "Enter number: ";
        int num;
        std::cin >> num;
        dir = dir_options[num];
    }

    editScript(argv[1], dir);
}

void editScript(std::string name, std::string dir)
{
    std::string script = dir + "/" + name;

    system((settings.getSetting<std::string>("editor") + " " + script).c_str());
}

void removeScript(int argc, char *argv[])
{


    std::map<int, std::string> dir_options;

    for (auto search_dir : settings.getSetting<std::vector<std::string>>("search_dirs"))
    {
        if (std::filesystem::exists(search_dir + "/" + argv[1]))
        {
            dir_options[dir_options.size()] = search_dir;
        }
    }

    if (dir_options.size() == 0)
    {
        std::cout << "Script " << argv[1] << " does not exist" << std::endl;
        return;
    }

    if (dir_options.size() == 1)
    {
        dir = dir_options[0];
    }

    if (dir_options.size() > 1)
    {
        std::cout << "Which script do you want to remove?" << std::endl;
        for (auto &option : dir_options)
        {
            std::cout << option.first << " " << option.second << std::endl;
        }
        std::cout << "Enter number: ";
        int num;
        std::cin >> num;
        dir = dir_options[num];
    }

    std::string script = dir + "/" + argv[1];
    if (std::filesystem::exists(script))
    {
        std::cout << "Removing script: " << argv[1] << std::endl;
        std::filesystem::remove(script);
    }
    else
    {
        std::cout << "Script " << argv[1] << " does not exist" << std::endl;
    }
}

// help function for showing help message
void help(int argc, char *argv[])
{
    std::cout << "Usage: autom [command] [options]" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "\t[script] - Runs a script if autom has not command with that name" << std::endl;
    std::cout << command.listCommands() << std::endl;
}