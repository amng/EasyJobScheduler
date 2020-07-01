#include "../includes/TaskManager.hpp"
#include <fstream>
#include <stdio.h>
#include <gtest/gtest.h>


class CoutRedirect {
    //code from:
    //https://stackoverflow.com/questions/5419356/redirect-stdout-stderr-to-a-string
public:
    CoutRedirect() {
        old = std::cout.rdbuf( buffer.rdbuf() ); // redirect cout to buffer stream
    }

    std::string getString() {
        return buffer.str(); // get string
    }

    ~CoutRedirect( ) {
        std::cout.rdbuf( old ); // reverse redirect
    }

private:
    std::stringstream buffer;
    std::streambuf * old;
};

struct TaskManagerTests : public ::testing::Test
{
};

TEST_F(TaskManagerTests, DetectCycleTest)
{
    TaskManager manager("D", std::vector<std::string>{"../tests/testData/D.task"});
    EXPECT_EQ(true, manager.isThereACyclicDependency());
}

TEST_F(TaskManagerTests, DetectCycleTest2)
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

TEST_F(TaskManagerTests, DetectNoCycle)
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

TEST_F(TaskManagerTests, UnexistingFile)
{
    TaskManager manager("C", std::vector<std::string>{"../tests/testData/nonexistingfile.task"});
    EXPECT_EQ(true, manager.didErrorHappen());
    EXPECT_EQ("Missing files: ../tests/testData/nonexistingfile.task, ", manager.getErrorMessage());
}

TEST_F(TaskManagerTests, ExistingFile)
{
    TaskManager manager("A", std::vector<std::string>{"../tests/testData/A.task"});
    EXPECT_EQ(false, manager.didErrorHappen());
}

TEST_F(TaskManagerTests, MissingDependency)
{
    TaskManager manager("C", std::vector<std::string>{"../tests/testData/C.task"});
    EXPECT_EQ(true, manager.isThereAMissingDependency());
}

TEST_F(TaskManagerTests, NoMissingDependency)
{
    TaskManager manager("C", std::vector<std::string>{
                                 "../tests/testData/C.task",
                                 "../tests/testData/A.task",
                                 "../tests/testData/B.task"});
    EXPECT_EQ(false, manager.isThereAMissingDependency());
}

TEST_F(TaskManagerTests, MissingDependencyMainTask)
{
    TaskManager manager("MISSING", std::vector<std::string>{"../tests/testData/C.task"});
    EXPECT_EQ(true, manager.isThereAMissingDependency());
}

TEST_F(TaskManagerTests, RunOneTask)
{
    TaskManager manager("A", std::vector<std::string>{"../tests/testData/A.task"});
    CoutRedirect cr;
    manager.run();
    EXPECT_EQ("'I am task A'\n", cr.getString());
}

TEST_F(TaskManagerTests, RunTaskWithDeps)
{
    TaskManager manager("C", std::vector<std::string>{"../tests/testData/A.task",
    "../tests/testData/B.task",
    "../tests/testData/C.task"});
    CoutRedirect cr;
    manager.run();
    EXPECT_EQ("'I am task A'\n'I am task B'\n'I am task C'\n", cr.getString());
}