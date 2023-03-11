cmake_minimum_required(VERSION 3.10)
project(WORLISTPARSE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

# 开启测试
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(demo ${PROJECT_SOURCE_DIR}/src/demo.cpp)

# 查找 GTest 库
find_package(GTest REQUIRED)
# GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(unit_test ${PROJECT_SOURCE_DIR}/src/unit_test.cpp)
target_link_libraries(unit_test ${GTEST_BOTH_LIBRARIES} pthread)
add_test(NAME unit_test COMMAND unit_test)