cmake_minimum_required(VERSION 3.25)

project(algo CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} 
    INTERFACE    
        ds
)
target_include_directories(${PROJECT_NAME} INTERFACE .)