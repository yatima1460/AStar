cmake_minimum_required(VERSION 3.22)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Please configure in a separate build directory.")
endif()

project(Pathfinding LANGUAGES CXX)

include(CTest)

add_library(Pathfinding Source/Pathfinder.cpp)
target_compile_features(Pathfinding PUBLIC cxx_std_17)
set_target_properties(Pathfinding PROPERTIES CXX_EXTENSIONS OFF)
target_include_directories(Pathfinding PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:include>
)

# Pathfinder.cpp uses std::numeric_limits without including <limits> itself.
target_precompile_headers(Pathfinding PRIVATE <limits>)

if(MSVC)
    target_compile_options(Pathfinding PRIVATE /W4)
else()
    target_compile_options(Pathfinding PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(BUILD_TESTING)
    add_subdirectory(Tests)
endif()
