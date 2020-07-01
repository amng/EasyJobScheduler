#pragma once

#include <string>
#include <vector>

class Task
{
private:
    std::string command;
    std::vector<std::string> dependencies;
public:

    /**
    * Runs the command that was set on the task creation
    */
    void executeTask();

    /**
    * Sets the command that will be executed when this task runs
    * @param command the command to run
    */
    void setCommand(std::string command);

    /**
    * Set the dependency tasks
    * @param dependencies the other tasks that must be run before this one
    */
    void setDependencies(std::vector<std::string> dependencies);

    const std::vector<std::string> & getDependencies();
};