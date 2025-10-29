cmake_minimum_required(VERSION 3.10)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC_FILES
    src/main.cpp
    src/domain/inf_int.cpp
    src/view/view.cpp
    src/service/calculator_service.cpp
    src/controller/calculator_controller.cpp
)

add_executable(Calculator ${SRC_FILES})
