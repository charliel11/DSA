cmake_minimum_required(VERSION 3.25)

project(DSA CXX)

add_subdirectory(algo)
add_subdirectory(ds)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} 
    INTERFACE 
        ${CMAKE_CURRENT_LIST_DIR}/algo 
    INTERFACE 
        ${CMAKE_CURRENT_LIST_DIR}/ds
)