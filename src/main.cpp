#include <iostream>
#include <string>
#include <sys/stat.h>

int main(int argc, char *argv[])
{

    // make dir in ~/autom
    std::string home = getenv("HOME");
    std::string dir = home + "/autom";
    // std::cout << "dir: " << dir << std::endl;
    mkdir(dir.c_str(), 0777);

    if (argc > 1 && argv[1][0] != '-')
    {
        std::string pre_script = "cd " + dir + " && ";
        std::string script = pre_script + dir + "/" + argv[1];
        system(script.c_str());
    }
    // else{
    //     std::cout << "Usage: autom <script>" << std::endl;
    // }

    return 0;
}