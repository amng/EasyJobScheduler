#include <cstdlib>
#include <iostream>
#include <memory>
#include "../includes/Task.hpp"

//to make it easier to test
void exec(const char *cmd)
{
    //code from:
    //https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
    std::array<char, 128> buffer;
    std::string res = "";
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        res += buffer.data();
    }
    std::cout << res;
}

void Task::executeTask()
{
    //TODO: add some checks (password needed? Command failed to execute?)
    exec(this->command.c_str());
}

void Task::setCommand(std::string command)
{
    this->command = command;
}

void Task::setDependencies(std::vector<std::string> dependencies)
{
    this->dependencies = dependencies;
}

const std::vector<std::string> &Task::getDependencies()
{
    return this->dependencies;
}