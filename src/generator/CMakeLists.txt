include_directories(${globalProject_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../bin")
add_executable(generator main.cpp figures.cpp )
target_link_libraries(generator lib)
