cmake_minimum_required(VERSION 3.20)

project(CLionProjectsoop2_team8_assigment)

set(CMAKE_CXX_STANDARD 20)

# 헤더들이 있는 경로들을 include path 에 추가
include_directories(
        ${PROJECT_SOURCE_DIR}/domain/include
        ${PROJECT_SOURCE_DIR}/domain/expr
        ${PROJECT_SOURCE_DIR}/domain/expr/include2
)

add_executable(CLionProjectsoop2_team8_assigment
        # 메인 실행부
        domain/main.cpp

        # Big-int 관련 소스
        domain/inf_int.cpp
        domain/operator.cpp
        domain/add.cpp
        domain/sub.cpp
        domain/mul.cpp
        domain/expr/src/Expr.cpp
        domain/expr/include2/Expr.h
        domain/expr/src/VariableExpr.cpp
        domain/expr/include2/VariableExpr.h
        domain/include/inf_int.h
        domain/include/operator.h
        domain/include/add.h
        domain/include/sub.h
        domain/include/mul.h
        domain/expr/include2/VariableExpr.h
        domain/expr/src/NumberExpr.cpp
        domain/expr/include2/NumberExpr.h
        domain/expr/src/BinaryExpr.cpp
        domain/expr/include2/BinaryExpr.h
        domain/expr/src/Parser.cpp
        domain/expr/include2/Parser.h
        domain/expr/EquationSolverService.cpp
        domain/expr/include2/EquationSolverService.h
        domain/expr/Evaluator.cpp
        domain/expr/include2/Evaluator.h
)
