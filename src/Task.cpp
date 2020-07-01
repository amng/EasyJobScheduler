#include "../includes/Task.hpp"

void Task::executeTask()
{
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