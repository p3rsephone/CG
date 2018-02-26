set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../bin")
add_executable(generator main.cpp)
install(TARGETS generator RUNTIME DESTINATION bin)
