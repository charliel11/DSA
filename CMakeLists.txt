cmake_minimum_required(VERSION 3.25)

project(LeetCode)

# enable_testing()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(external/googletest)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} DSA)
# target_link_libraries(${PROJECT_NAME} GTest::gtest_main)

# include(GoogleTest)
# gtest_discover_tests(LeetCode)