# Run 'cmake ..' from the 'bin/' directory to create makefile then run
# 'make' to build the project.

# Project info
cmake_minimum_required (VERSION 3.1.0)
project                (OpenGL)

# Subdirectories
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/inc)
set(SOURCE_DIR  ${CMAKE_SOURCE_DIR}/src)

# Compiler flags
set(GCC_COMPILE_FLAGS "-g -Wall -O3")
set(GCC_LINK_FLAGS    "-lGL -lGLEW -lm -lSOIL")

set(CMAKE_C_FLAGS "${GCC_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")

# Linking GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Fetching files for compiler
include_directories("${INCLUDE_DIR} ${GLFW_INCLUDE_DIRS}")
file(GLOB SOURCES "${SOURCE_DIR}/*.c")
add_executable(OpenGL ${SOURCES})
target_link_libraries(OpenGL ${GLFW_LIBRARIES})
