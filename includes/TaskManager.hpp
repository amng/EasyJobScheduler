#pragma once

#include "Task.hpp"
#include <vector>
#include <string>
#include <unordered_map>

class TaskManager
{
private:
    std::string mainTask;
    bool errorState = false;
    std::vector<std::string> missingFiles;
    std::unordered_map<std::string, Task *> tasksMap;

    /**
    * Reads a file and creates a task from that information inserting it into the tasks map
    * @param filePath the file path 
    */
    void addTaskFromFile(std::string filePath);

    /**
     * Parses a line from the textfile with the dependencies of the task 
     * TODO: use boost library probably to do a split and trim of the tasks
     * @param line the line from the file that needs to be converted into a string vector
     * @return the list of task names that are dependencies to a specific task
     */
    std::vector<std::string> parseDependencies(std::string line);

    /**
     * Uses depth first search to check if there are cyclic dependencies
     * @param task the task that will be used to grab other dependencies
     * @param previousTasks the list of tasks that were already found so we can check if there is a cycle
     * @return whether or not there is a cycle in the dependencies
    */
    bool isThereACyclicDependencyHelper(Task *task, std::vector<Task *> & previousTasks);
    
    /**
     * Uses depth first search to check if there are any missing dependencies
     * @param task the task that will be used to grab other dependencies
     * @return whether or not there is a missing dependency
    */
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
     * TODO: add more checks
     * @return Whether or not an error happened during parsing of the files
     */
    bool didErrorHappen();
    
    /**
     * Executes main task which will in turn run all needed dependencies
     */
    void run();
};