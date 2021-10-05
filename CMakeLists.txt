cmake_minimum_required(VERSION 3.8)

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

project(Preon)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(PREON_VERSION "0.1.0-dev")
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/CompileConfig.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/CompileConfig.h"
)

find_package(SDL2 CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(Threads REQUIRED)
find_package(TIDY REQUIRED)
find_package(Freetype REQUIRED)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/quickjspp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CURL_INCLUDE_DIRS} ${TIDY_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} SDL2::SDL2 ${CMAKE_CURRENT_SOURCE_DIR}/deps/)

file(GLOB_RECURSE PREON_SRC
${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp 
)

file(GLOB_RECURSE INIH_SRC
${CMAKE_CURRENT_SOURCE_DIR}/deps/inih/ini.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/deps/inih/INIReaders.cpp 
)

file(GLOB_RECURSE TINYXML2_SRC
${CMAKE_CURRENT_SOURCE_DIR}/deps/tinyxml2/tinyxml2.cpp
)

link_libraries(${CURL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${TIDY_LIBRARIES} SDL2::SDL2 ${FREETYPE_LIBRARIES})

add_executable(${PROJECT_NAME} ${PREON_SRC} ${INIH_SRC} ${TINYXML2_SRC})