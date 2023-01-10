cmake_minimum_required(VERSION 3.11)

project(chess-v3-tests CXX)

enable_testing()

add_executable(${PROJECT_NAME}
    "board_tests.cc"
    "piece_tests.cc"
    "point_tests.cc"
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} chess-v3 GTest::gtest_main)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:chess-v3> $<TARGET_FILE_DIR:${PROJECT_NAME}>)
