#pragma once

#include <string>// std::fabs
#include "Parser.h"     // Expr, NumberExpr, VariableExpr, BinaryExpr, BinaryOp 등을 쓸 거니까

struct LinearForm {
    double a;
    double b;
};

class EquationSolverService {
public:
    std::string solveEquationLine(const std::string& line);

private:
    LinearForm evalLinear(Expr* e);

    double infIntToDouble(const inf_int& v);

    void deleteExpr(Expr* e);
};
