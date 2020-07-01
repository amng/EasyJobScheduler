#include <fstream>
#include <algorithm>
#include <iostream>
#include "../includes/TaskManager.hpp"

std::vector<std::string> TaskManager::parseDependencies(std::string line)
{
    std::string temp;
    std::vector<std::string> res;
    for(int i = 0; i < line.size(); i++)
    {
        if (line[i] != ',')
        {
            temp += line[i];
        }
        if  (line[i] == ',' || i == line.size()-1)
        {
            res.push_back(temp);
            temp = "";
            i++; //skip the space after the comma (Really bad :( )
        }
    }
    return res;
} 

void TaskManager::addTaskFromFile(std::string filePath)
{
    Task *task = new Task();
    //no need to close since ifstream uses RAII
    std::ifstream infile(filePath);
    int i = 0;
    std::string taskName;
    std::cout << "=========================================================>>>>>>>FILE CONTENTS" << std::endl;
    for (std::string line; std::getline( infile, line ); i++)
    {
        std::cout << line << std::endl;
        switch (i)
        {
        case 0:
            taskName = line;
            break;
        case 1: 
            task->setCommand(line);
            break;
        case 2:
            task->setDependencies(parseDependencies(line));
        default:
            break;
        } 
    }
    tasksMap[taskName] = task;
}

TaskManager::TaskManager(std::string task, std::vector<std::string> fileNames) : mainTask(task)
{
    for (std::string &taskFile : fileNames)
    {
        addTaskFromFile(taskFile);
    }
}

/**
 * Cleans up all the tasks that were created in the beggining
 */
TaskManager::~TaskManager()
{
    for (auto task : tasksMap)
    {
        delete task.second;
    }
    tasksMap.clear();
}

/**
 * Executes main task which will in turn run all needed dependencies
 */
void TaskManager::run()
{
}

bool TaskManager::isThereACyclicDependencyHelper(Task *task, std::vector<Task *> & previousTasks)
{
    if (std::find(previousTasks.begin(), previousTasks.end(), task) != previousTasks.end())
        return true;
    previousTasks.push_back(task);
    for (const std::string & nextTask : task->getDependencies())
    {
        if (isThereACyclicDependencyHelper(tasksMap[nextTask], previousTasks))
            return true;
    }
    return false;
}

bool TaskManager::isThereACyclicDependency()
{
    std::vector<Task *> previousTasks;
    return isThereACyclicDependencyHelper(tasksMap[mainTask], previousTasks);
}
