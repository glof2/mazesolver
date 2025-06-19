cmake_minimum_required(VERSION 4.0)
project(mazesolver)

# Get source files
file(GLOB SOURCES "source/*.cpp")
list(APPEND SOURCES "main.cpp")

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX-STANDARD_REQUIRED True)

# Executable
add_executable(mazesolver ${SOURCES})

# Includes
target_include_directories(mazesolver PRIVATE header)
