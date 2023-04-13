cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CUDA_ARCHITECTURES 86)
project(LeetCode LANGUAGES C CXX)

find_package(OpenMP REQUIRED)

# message("Your C++ compiler supports these C++ features:")

# foreach(i ${CMAKE_CXX_COMPILE_FEATURES})
# message("${i}")
# endforeach()
if(PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(WARNING "The binary directory of CMake cannot be the same as source directory!")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(WIN32)
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(external/googletest)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE DSA)
target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECTDIR="${PROJECT_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)