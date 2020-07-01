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