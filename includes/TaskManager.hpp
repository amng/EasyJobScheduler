#pragma once

#include "Task.hpp"
#include <vector>
#include <string>
#include <unordered_map>

class TaskManager
{
private:
    bool errorState = false;
    std::vector<std::string> missingFiles;
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
    bool isThereAMissingDependencyHelper(Task *task);
    
    /**
    * @param task the task that will run along with all its dependencies
    */
    void runHelper(Task * task);
public:
    /**
    * @param task the main task that will be run together with its dependencies
    * @param fileNames the files where the tasks are defined
    */
    TaskManager(std::string task, std::vector<std::string> fileNames); 

    /**
     * Cleans up all the tasks that were created in the beggining
     */
    ~TaskManager();

    /**
     * Returns the error message for the error
     * This function should be called after TaskManager::didErrorHappen()
     * @return the error message 
     */
    std::string getErrorMessage();

    /**
     * @return whether or not there are cyclic dependencies for the tasks 
     */
    bool isThereACyclicDependency();

    /**
     * @return whether or not there is a missing dependency 
     **/
    bool isThereAMissingDependency();
    
    /**
     * @return Whether or not an error happened during parsing of the files
     * TODO: add more checks
     */
    bool didErrorHappen();
    
    /**
     * Executes main task which will in turn run all needed dependencies
     */
    void run();
};