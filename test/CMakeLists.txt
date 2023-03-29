cmake_minimum_required(VERSION 3.25)

project(TestDSA CXX)

file(GLOB files ${PROJECT_SOURCE_DIR} *.cpp)

message(STATUS "files: ${files}")

add_executable(${PROJECT_NAME} ${files})
target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        DSA
    PUBLIC
        gtest_main
)