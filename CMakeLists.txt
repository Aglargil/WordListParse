cmake_minimum_required(VERSION 3.10)
project(WORLISTPARSE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

# 开启测试
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/inc)

add_subdirectory(demo)
add_subdirectory(test)

add_test(NAME unit_test COMMAND unit_test)