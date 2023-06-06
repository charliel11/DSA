cmake_minimum_required(VERSION 3.20)

project(DSA LANGUAGES C CXX)

file(GLOB_RECURSE srcs CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR} src/*.cpp include/*.h)

add_library(${PROJECT_NAME} STATIC ${srcs})
target_include_directories(${PROJECT_NAME}
    PUBLIC
    include
)