#pragma once

#include "Task.hpp"
#include <vector>
#include <string>
#include <unordered_map>

class TaskManager
{
private:
    /**
    * Reads a file and creates a task from that information inserting it into the tasks map
    * @param filePath the file path 
    */
    void addTaskFromFile(std::string filePath);

    /**
     * Parses a line from the textfile with the dependencies of the task 
     * TODO: use boost library probably to do a split and trim of the tasks
     */
    std::vector<std::string> parseDependencies(std::string line);
    std::string mainTask;
    std::unordered_map<std::string, Task *> tasksMap;
    bool isThereACyclicDependencyHelper(Task *task, std::vector<Task *> & previousTasks);

public:
    TaskManager(std::string task, std::vector<std::string> fileNames); 
    ~TaskManager();
    bool isThereACyclicDependency();
    void run();
};