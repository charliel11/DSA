cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(algo LANGUAGES C CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} 
    INTERFACE    
        ds
)
target_include_directories(${PROJECT_NAME} INTERFACE .)