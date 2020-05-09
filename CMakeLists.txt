cmake_minimum_required(VERSION 3.5.1)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()



# Create project
project(Pathfinding)
set(CMAKE_CXX_STANDARD 17)
include_directories(Include)
file(GLOB_RECURSE SOURCES Source/*.cpp)
add_library(Pathfinding ${SOURCES})

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")
endif()


enable_testing()
add_subdirectory(Tests)
