cmake_minimum_required(VERSION 3.11)

project(chess-v1 CXX)

add_library(${PROJECT_NAME} SHARED
    "board.cc"
    "piece.cc"
    "point.cc"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../include")
