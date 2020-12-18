cmake_minimum_required(VERSION 3.17)
project(FormalPrac1)

set(CMAKE_CXX_STANDARD 14)

add_library(Algo STATIC include/Algo.cpp)
add_library(Grammar_t STATIC include/Grammar_t.cpp)
target_link_libraries(Algo Grammar_t)

add_executable(FormalPrac2 main.cpp)
target_include_directories(FormalPrac2 PUBLIC include)
target_link_libraries(FormalPrac2 Algo)

find_package(GTest REQUIRED)

add_executable(Testing testing/test_init.cpp testing/test.cpp)
target_include_directories(Testing PUBLIC include)
target_link_libraries(Testing Algo ${GTEST_BOTH_LIBRARIES} Threads::Threads)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/extern_modules)
include(code_coverage)
append_coverage_compiler_flags()
setup_target_for_coverage_gcovr_html(NAME coverage EXECUTABLE Testing EXCLUDE test main.cpp)