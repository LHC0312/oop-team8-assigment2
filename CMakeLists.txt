cmake_minimum_required(VERSION 4.0)
project(CLionProjectsoop2_team8_assigment)

set(CMAKE_CXX_STANDARD 20)

add_executable(CLionProjectsoop2_team8_assigment
        cmake-build-debug/domain/inf_int.cpp
        cmake-build-debug/domain/include/inf_int.h
        cmake-build-debug/domain/main.cpp
        cmake-build-debug/domain/operator.cpp
        cmake-build-debug/domain/include/operator.h
        cmake-build-debug/domain/add.cpp
        cmake-build-debug/domain/include/add.h
        cmake-build-debug/domain/sub.cpp
        cmake-build-debug/domain/include/sub.h
        cmake-build-debug/domain/mul.cpp
        cmake-build-debug/domain/include/mul.h
)
