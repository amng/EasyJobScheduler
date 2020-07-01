#include <iostream>
#include "../includes/TaskManager.hpp"

int main(int argsCount, char** argsValues) {
    if (argsCount == 1)
    {
        std::cout << "Please provide at least one task to execute!" << std::endl;
    }
    std::vector<std::string> taskFiles;
    taskFiles.reserve(argsCount-1);
    for (int i = 1; i < argsCount; i++)
    {
        taskFiles.push_back(argsValues[i]);
    }
    std::string mainTask = argsValues[0];
    TaskManager manager(mainTask, taskFiles);
    manager.run();    
}
