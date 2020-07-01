cmake_minimum_required(VERSION 3.0.0)
project(EasyJobScheduler VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")


file(GLOB EasyJobScheduler_SRC "src/*.cpp")
add_executable(EasyJobScheduler ${EasyJobScheduler_SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)



################################
# GTest
################################

# ===============================
# Download and install GoogleTest
# ===============================
include(ExternalProject)
ExternalProject_Add(gtest URL https://github.com/google/googletest/archive/release-1.7.0.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libs/gtest
  INSTALL_COMMAND ""
)
ExternalProject_Get_Property(gtest source_dir binary_dir)


# Define a test
file(GLOB EasyJobScheduler_TEST_SRC "src/*.cpp")
list(REMOVE_ITEM EasyJobScheduler_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
list(APPEND EasyJobScheduler_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit_tests.cpp)

add_executable(EasyJobScheduler_tests ${EasyJobScheduler_TEST_SRC})

add_dependencies(EasyJobScheduler_tests gtest)
include_directories(${source_dir}/include)
target_link_libraries(EasyJobScheduler_tests ${binary_dir}/libgtest.a ${binary_dir}/libgtest_main.a)

##################################
# Just make the test runnable with
#   $ make test

enable_testing()
include(GoogleTest)
gtest_discover_tests(EasyJobScheduler_tests)