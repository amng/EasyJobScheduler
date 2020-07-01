#include "../includes/TaskManager.hpp"
#include "gtest/gtest.h"

TEST(TaskManagerTests, DetectCycleTest)
{
    TaskManager manager("D", std::vector<std::string>{"../tests/testData/D.task"});
    EXPECT_EQ(true, manager.isThereACyclicDependency());
}

TEST(TaskManagerTests, DetectCycleTest2)
{
    TaskManager manager("E", std::vector<std::string>{
                                 "../tests/testData/A.task",
                                 "../tests/testData/B.task",
                                 "../tests/testData/C.task",
                                 "../tests/testData/D.task",
                                 "../tests/testData/E.task",
                                 "../tests/testData/F.task"});
    EXPECT_EQ(true, manager.isThereACyclicDependency());
}

TEST(TaskManagerTests, DetectNoCycle)
{
    TaskManager manager("C", std::vector<std::string>{
                                 "../tests/testData/A.task",
                                 "../tests/testData/B.task",
                                 "../tests/testData/C.task",
                                 "../tests/testData/D.task",
                                 "../tests/testData/E.task",
                                 "../tests/testData/F.task"});
    EXPECT_EQ(false, manager.isThereACyclicDependency());
}

TEST(TaskManagerTests, UnexistingFile)
{
    TaskManager manager("C", std::vector<std::string>{"../tests/testData/nonexistingfile.task"});
    EXPECT_EQ(true, manager.didErrorHappen());
    EXPECT_EQ("Missing files: ../tests/testData/nonexistingfile.task, ", manager.getErrorMessage());
}

TEST(TaskManagerTests, ExistingFile)
{
    TaskManager manager("A", std::vector<std::string>{"../tests/testData/A.task"});
    EXPECT_EQ(false, manager.didErrorHappen());
}

TEST(TaskManagerTests, MissingDependency)
{
    TaskManager manager("C", std::vector<std::string>{"../tests/testData/C.task"});
    EXPECT_EQ(true, manager.isThereAMissingDependency());
}

TEST(TaskManagerTests, NoMissingDependency)
{
    TaskManager manager("C", std::vector<std::string>{
                                 "../tests/testData/C.task",
                                 "../tests/testData/A.task",
                                 "../tests/testData/B.task"});
    EXPECT_EQ(false, manager.isThereAMissingDependency());
}