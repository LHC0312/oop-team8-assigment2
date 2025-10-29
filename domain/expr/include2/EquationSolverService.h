#pragma once

#include <string>
#include "Parser.h"
#include "Evaluator.h" // LinearForm, etc.

class EquationSolverService {
public:
    std::string solveEquationLine(const std::string& line);

private:
    // Expr* 트리를 ax+b 형태의 LinearForm으로 해석한다.
    LinearForm evalLinear(Expr* e);

    // inf_int -> double 변환 헬퍼
    double infIntToDouble(const inf_int& v);

    // 재귀적으로 Expr* 트리를 지우는 헬퍼
    void deleteExpr(Expr* e);
};
