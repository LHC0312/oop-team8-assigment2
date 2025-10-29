#pragma once
#include "Expr.h" // Expr 클래스를 알아야 함
#include "../include/inf_int.h" // inf_int를 알아야 함
#include <string>

class Equation {
public:
    Equation();

    /**
     * @brief AST를 받아서 알아서 처리 (방정식 풀기 또는 값 계산)
     * @param ast 파서가 생성한 AST의 루트 노드
     * @param varName 방정식/계산에 사용될 변수 이름 (예: "x")
     * @param evalValue 방정식이 아닐 경우, 계산에 사용할 값 (예: x=3)
     */
    void process(Expr* ast, const std::string& varName, const inf_int& evalValue);

private:
    /**
     * @brief 방정식을 푸는 내부 로직
     */
    void solveEquation(Expr* ast, const std::string& varName);

    /**
     * @brief 단순 표현식을 계산하는 내부 로직
     */
    void evaluateExpression(Expr* ast, const std::string& varName, const inf_int& varValue);
};