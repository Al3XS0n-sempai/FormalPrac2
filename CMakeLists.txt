cmake_minimum_required(VERSION 3.17)
project(FormalPrac1)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB GRAMMARS
    "Grammars/*.txt"
)
file(COPY ${GRAMMARS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_library(Algo STATIC include/Algo.cpp)
add_library(Grammar_t STATIC include/Grammar_t.cpp)
target_link_libraries(Algo Grammar_t)

add_executable(FormalPrac2 main.cpp)
target_include_directories(FormalPrac2 PUBLIC include)
target_link_libraries(FormalPrac2 Algo)

find_package(GTest REQUIRED)

add_executable(Testing_Algo testing/test_init.cpp testing/test_algo.cpp)
target_include_directories(Testing_Algo PUBLIC include)
target_link_libraries(Testing_Algo Algo ${GTEST_BOTH_LIBRARIES} Threads::Threads)

add_executable(Testing_Grammar testing/test_init.cpp testing/test_grammar.cpp)
target_include_directories(Testing_Grammar PUBLIC include)
target_link_libraries(Testing_Grammar Grammar_t ${GTEST_BOTH_LIBRARIES} Threads::Threads)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/extern_modules)
include(code_coverage)
append_coverage_compiler_flags()
setup_target_for_coverage_gcovr_html(NAME coverage_grammar EXECUTABLE Testing_Grammar EXCLUDE test main.cpp)
setup_target_for_coverage_gcovr_html(NAME coverage_algo EXECUTABLE Testing_Algo EXCLUDE test main.cpp)