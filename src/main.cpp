#include <iostream>
#include "../includes/TaskManager.hpp"

int main(int argsCount, char** argsValues) {
    if (argsCount < 3)
    {
        std::cout << "Please provide at least one task to execute!" << std::endl;
    }
    std::vector<std::string> taskFiles;
    taskFiles.reserve(argsCount-2);
    for (int i = 2; i < argsCount; i++)
    {
        taskFiles.push_back(argsValues[i]);
    }
    std::string mainTask = argsValues[1];
    TaskManager manager(mainTask, taskFiles);
    if (manager.didErrorHappen())
    {
        std::cout << "Error: " << manager.getErrorMessage() << std::endl;
        exit(-1);
    }
    if (manager.isThereACyclicDependency()){
        std::cout << "Error: There's a cyclic dependency in your tasks!";
        exit(-1);
    }
    if (manager.isThereAMissingDependency())
    {
        std::cout << "Error: There's at least one missing dependency!";
        exit(-1);
    }
    manager.run();    
}
