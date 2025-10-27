cmake_minimum_required(VERSION 3.26)
project(Calculator)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(src/main/*)

# Source files
file(GLOB_RECURSE SOURCES 
    "src/main/*.cpp"
)

add_executable(Calculator ${SOURCES})