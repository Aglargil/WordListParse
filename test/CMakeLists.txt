# 查找 GTest 库
find_package(GTest REQUIRED)
# GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS})

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
add_executable(unit_test ${SRC_LIST} unit_test.cpp)
target_link_libraries(unit_test ${GTEST_BOTH_LIBRARIES} pthread)