project(TestDSA CXX)

file(GLOB files CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR} *.cpp *.h)

# message(STATUS "files: ${files}")
add_executable(${PROJECT_NAME} ${files})

# add_executable(${PROJECT_NAME} test_graph.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
    DSA
    GTest::gtest_main
    GTest::gtest
)
target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECTDIR="${PROJECT_SOURCE_DIR}")

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/bin"
)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:GTest::gtest_main>
    $<TARGET_FILE:GTest::gtest>
    $<TARGET_FILE:DSA>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)