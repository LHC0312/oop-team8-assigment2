cmake_minimum_required(VERSION 4.0)
project(CLionProjectsoop2_team8_assigment)

set(CMAKE_CXX_STANDARD 20)

add_executable(CLionProjectsoop2_team8_assigment
        domain/inf_int.cpp
        domain/include/inf_int.h
        domain/main.cpp
        domain/operator.cpp
        domain/include/operator.h
        domain/add.cpp
        domain/include/add.h
        domain/sub.cpp
        domain/include/sub.h
        domain/mul.cpp
        domain/include/mul.h
)
