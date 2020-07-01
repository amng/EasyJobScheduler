#include <cstdlib>
#include "../includes/Task.hpp"

void Task::executeTask()
{
    //TODO: add some checks (password needed? Command failed to execute?)
    std::system(this->command.c_str()); 
}

void Task::setCommand(std::string command)
{
    this->command = command;
}

void Task::setDependencies(std::vector<std::string> dependencies)
{
    this->dependencies = dependencies;
}

const std::vector<std::string> & Task::getDependencies()
{
    return this->dependencies;
}