// Equation.cpp
#include "../include2/Equation.h" // 1. 헤더 이름 변경
#include "../include2/BinaryExpr.h"
#include <iostream>

// 2. 클래스 이름 변경
Equation::Equation() {} 

// 3. 클래스 이름 변경
void Equation::process(Expr* ast, const std::string& varName, const inf_int& evalValue) {
    if (ast == nullptr) {
        std::cerr << "[Error] AST is null.\n";
        return;
    }

    if (ast->isEquation()) {
        solveEquation(ast, varName); // 4. 함수 이름 변경
    } else {
        evaluateExpression(ast, varName, evalValue); // 5. 함수 이름 변경
    }
}

// 6. 클래스/함수 이름 변경
void Equation::solveEquation(Expr* ast, const std::string& varName) {
    std::cout << "[LOG] Solving equation...\n";
    
    BinaryExpr* equation = static_cast<BinaryExpr*>(ast); 
    Expr* lhs = equation->getLeft();
    Expr* rhs = equation->getRight();

    bool found = false;
    for (int i = -1000; i <= 1000; ++i) {
        inf_int testValue(std::to_string(i).c_str());
        if (lhs->evaluate(varName, testValue) == rhs->evaluate(varName, testValue)) {
            std::cout << "Solution found: " << varName << " = " << testValue << std::endl; 
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "No integer solution found." << std::endl;
    }
}

// 7. 클래스/함수 이름 변경
void Equation::evaluateExpression(Expr* ast, const std::string& varName, const inf_int& varValue) {
    std::cout << "[LOG] Evaluating expression...\n";
    std::cout << "[LOG] Evaluating with " << varName << " = " << varValue << std::endl;
    
    inf_int result = ast->evaluate(varName, varValue);
    
    std::cout << "Result: " << result << std::endl;
}