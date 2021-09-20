cmake_minimum_required(VERSION 3.13)
project(quickjspp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

if(CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-Wall -Wno-unused-parameter)
endif()

add_subdirectory(quickjs)
#add_executable(qjs qjs.cpp)
link_libraries(qjs quickjs)
include_directories(.)

#enable_testing()
#add_subdirectory(test)
