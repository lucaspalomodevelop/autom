#include "main.h"

int main(int argc, char *argv[])
{

    Settings &settings = Settings::Instance();
    command = Command();

    home_dir = settings.value["autom_home_dir"];

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
    command.addCommandAlias("help", "h");
    command.addCommand("ls", "- Lists all scripts ", listScripts);
    command.addCommandAlias("ls", "l");
    command.addCommand("add", "[script] - Adds a script", addScript);
    command.addCommandAlias("add", "a");
    command.addCommand("edit", "[script] - Edits a script", editScript);
    command.addCommandAlias("edit", "e");
    command.addCommand("remove", "[script] - Remove a script", removeScript);
    command.addCommandAlias("remove", "r");
    command.addCommand("show", "[script] - Shows a script", showScript);
    command.addCommandAlias("show", "s");
    command.addCommand("config", "<command> - Configures autom", config);

    command.addDefaultCommand(runScript);
    command.runCommand(argv[1], argc, argv);
}

std::string scriptBuilder(std::string script, std::string args, json script_settings)
{

    std::string builded_script = "";
    builded_script = script;

    if (script_settings.contains("sudo") && script_settings.at("sudo").get<bool>())
        builded_script = "sudo " + script;

    if (script_settings.contains("pre_script") && script_settings.at("pre_script").size() > 0)
        builded_script = script_settings.at("pre_script").get<std::string>() + " && " + builded_script;

    if (script_settings.contains("args") && script_settings.at("args").size() > 0)
        builded_script = builded_script + " " + script_settings.at("args").get<std::string>();

    if (script_settings.contains("background") && script_settings.at("background").get<bool>())
        builded_script = builded_script + " &";

    // std::cout << "script: " << builded_script << std::endl;

    return builded_script;
}

automScript parse(const std::string filecontent)
{

    // std::cout << "filecontent before parse: " << filecontent << std::endl;
    std::stringstream file(filecontent);

    std::string line, content, script;
    int braceCount = 0;
    bool isSettings = false;
    bool start = false;
    while (std::getline(file, line))
    {
        for (char c : line)
        {
            if (c == '{')
            {
                braceCount++;
                isSettings = true;
            }
            if (c == '}')
                braceCount--;
            if (braceCount == 0 && isSettings)
            {
                content += c;
                isSettings = false;
                continue;
            }
            if (isSettings)
            {
                content += c;
            }
            else
            {
                script += c;
            }
        }
        content += '\n';
        if (!isSettings)
        {
            script += '\n';
        }
    }

    automScript result;
    try
    {
        result.settings = json::parse(content);
    }
    catch (json::parse_error &e)
    {
        result.settings = json::parse("{}");
    }
    result.script = script;

    // std::cout << "settings: " << result.settings << std::endl;
    // std::cout << "script: " << result.script << std::endl;

    return result;
}

automScript parseAndWriteBack(std::string script)
{
    std::ifstream file(script);
    std::string filecontent;
    std::string line;
    while (std::getline(file, line))
    {
        filecontent += line + "\n";
    }
    file.close();

    automScript parsed = parse(filecontent);

    std::ofstream file2(script);
    // std::cout << "script: " << parsed.script << std::endl;
    file2 << parsed.script;
    file2.close();

    return parsed;
}

std::string saveScriptInTemp(std::string script)
{
    std::string temp_file = settings.value["temp_dir"].get<std::string>() + "/autom_script";
    std::ofstream file(temp_file);

    std::string script_content = "";
    std::ifstream file2(script);
    std::string line;

    while (std::getline(file2, line))
    {
        file << line << std::endl;
    }

    file.flush();
    file.close();

    std::filesystem::permissions(temp_file, std::filesystem::perms::owner_all | std::filesystem::perms::group_all | std::filesystem::perms::others_all);

    return temp_file;
}

void cleanTempFile()
{
    std::string temp_file = settings.value["temp_dir"].get<std::string>() + "/autom_script";
    std::filesystem::remove(temp_file);
}

json mergeJson(json a, json b)
{
    json result = a;
    for (auto &el : b.items())
    {
        // std::cout << "key: " << el.key() << " value: " << el.value() << std::endl;
        result[el.key()] = el.value();
    }
    return result;
}

// run a script with is in the autom directory
void runScript(int argc, char *argv[])
{

    std::map<int, std::string> dir_options;
    std::string dir = home_dir;

    auto script_settings = settings.value["scripts"][argv[1]];

    for (auto search_dir : settings.value["search_dirs"])
    {
        if (std::filesystem::exists((std::string)search_dir + "/" + argv[1]))
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
        std::cout << "Which script do you want to run?" << std::endl;
        for (auto &option : dir_options)
        {
            std::cout << option.first << " " << option.second << std::endl;
        }
        std::cout << "Enter number: ";
        int num;
        std::cin >> num;
        dir = dir_options[num];
    }

    // for (auto search_dir : settings.getSetting<std::vector<std::string>>("search_dirs"))
    // {
    std::string script = dir + "/" + argv[1];
    if (std::filesystem::exists(script))
    {
        std::string pre_script = "cd " + dir + " && ";
        std::string args = "";
        std::string original_script = script;

        // std::cout << "original script: " << original_script << std::endl;

        for (int i = 2; i < argc; i++)
        {
            args += argv[i];
            args += " ";
        }
        // std::string script = pre_script + dir + "/" + argv[1] + " " + args;

        script = saveScriptInTemp(script);

        // std::cout << "script: " << script << std::endl;

        json json_settings = parseAndWriteBack(script).settings;

        script_settings = mergeJson(script_settings, json_settings);

        script = scriptBuilder(script, args, script_settings);

        // std::cout << "executing: " << (script + " " + args) << std::endl;

        // if (script_settings["sudo"])
        //     script = "sudo " + script;

        // if (script_settings["background"])
        //     script = script + " &";

        // if (script_settings["pre_script"].size() > 0)
        //     system(script_settings["pre_script"].get<std::string>().c_str());

        system(script.c_str());

        // cleanTempFile();
        return;
    }
    // }
}

void config(int argc, char *argv[])
{

    if (argc < 1)
    {
        std::cout << "Usage: autom config <command>" << std::endl;
        return;
    }

    if (std::string(argv[1]) == "show")
    {
        std::cout << "Settings:" << std::endl;
        std::cout << settings.getSettingsAsString() << std::endl;
    }

    else if (std::string(argv[1]) == "edit")
    {
        if (argc > 2)
        {
            if (std::string(argv[2]) == "editor")
            {

                std::string editor;
                if (argc > 3)
                    editor = argv[3];
                else
                {
                    std::cout << "Enter editor: ";
                    std::cin >> editor;
                }

                settings.value["editor"] = editor;
                settings.writeSettings();
                return;
            }
            return;
        }
        else
        {
            system((std::string(settings.value["editor"]) + " " + settings.filepath).c_str());
        }
    }

    // if (argv[2] == "editor")
    // {
    //     std::cout << "Enter editor: ";
    //     std::string editor;
    //     std::cin >> editor;
    //     settings.value["editor"] = editor;
    //     settings.save();
    //     return;
    // }

    // if (argv[2] == "search_dirs")
    // {
    //     std::cout << "Enter search dirs: ";
    //     std::string search_dirs;
    //     std::cin >> search_dirs;
    //     settings.value["search_dirs"] = search_dirs;
    //     settings.save();
    //     return;
    // }

    // if (argv[2] == "scripts")
    // {
    //     std::cout << "Enter scripts: ";
    //     std::string scripts;
    //     std::cin >> scripts;
    //     settings.value["scripts"] = scripts;
    //     settings.save();
    //     return;
    // }

    // std::cout << "Command " << argv[2] << " does not exist" << std::endl;
}

void showScript(int argc, char *argv[])
{

    std::map<int, std::string> dir_options;
    std::string dir = "";
    for (auto search_dir : settings.value["search_dirs"])
    {
        if (std::filesystem::exists((std::string)search_dir + "/" + argv[1]))
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

    for (auto &search_dir : settings.value["search_dirs"])
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
    std::string dir = home_dir;

    if (settings.value["search_dirs"].size() > 1)
    {
        std::cout << "Which directory do you want to add the script to?" << std::endl;
        auto search_dirs = settings.value["search_dirs"];
        for (int i = 0; i < search_dirs.size(); i++)
        {
            std::cout << i << " " << search_dirs[i] << std::endl;
        }
        std::cout << "Enter number: ";
        int num;
        std::cin >> num;
        dir = search_dirs[num];
    }

    if (std::filesystem::exists(dir + "/" + argv[1]))
    {
        std::cout << "Script " << argv[1] << " in folder " << dir << " already exists" << std::endl;
        return;
    }

    std::cout << "Adding script: " << argv[1] << std::endl;
    std::string script = dir + "/" + argv[1];
    std::ofstream file(script);

#ifdef _WIN32
    file << "@echo off" << std::endl;
    _chmod(script.c_str(), _S_IREAD | _S_IWRITE);
#else
    file << "#!/bin/bash" << std::endl;
    system(("chmod +x " + script).c_str());
#endif

    file.close();

    editScript(argv[1], dir);
}

// edit a script in the autom directory
void editScript(int argc, char *argv[])
{

    std::map<int, std::string> dir_options;
    std::string dir = home_dir;

    for (auto search_dir : settings.value["search_dirs"])
    {
        if (std::filesystem::exists((std::string)search_dir + "/" + argv[1]))
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

    system(((std::string)settings.value["editor"] + " " + script).c_str());
}

void removeScript(int argc, char *argv[])
{

    std::map<int, std::string> dir_options;
    std::string dir = home_dir;

    for (auto search_dir : settings.value["search_dirs"])
    {
        if (std::filesystem::exists((std::string)search_dir + "/" + argv[1]))
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