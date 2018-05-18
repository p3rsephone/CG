
cmake_minimum_required(VERSION 3.9)

find_package(DevIL REQUIRED)
link_libraries(${IL_LIBRARIES} )
include_directories(§{IL_INCLUDE_DIR})
if(NOT DevIL_FOUND)
  message(ERROR " Devil not found!")
endif(NOT DevIL_FOUND)





include_directories(${globalProject_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../bin")
add_executable(generator generator.cpp Figure.cpp Patch.cpp PatchParser.cpp)
target_link_libraries(generator lib ${IL_LIBRARIES})
