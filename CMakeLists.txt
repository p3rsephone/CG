cmake_minimum_required(VERSION 3.9)
project(globalProject)
set(CMAKE_CXX_STANDARD 11)
include_directories(${globalProject_SOURCE_DIR}/lib)
add_subdirectory(src/engine)
add_subdirectory(src/generator)
add_subdirectory(lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
