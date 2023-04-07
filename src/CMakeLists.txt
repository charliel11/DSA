cmake_minimum_required(VERSION 3.25)

project(DSA LANGUAGES C CXX)

add_subdirectory(algo)
add_subdirectory(ds)

file(GLOB_RECURSE files CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR} *.cpp *.h)

add_library(${PROJECT_NAME} ${files})
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/algo
    ${CMAKE_CURRENT_LIST_DIR}/ds
    .
)