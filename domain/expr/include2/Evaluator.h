#pragma once
#include "../../include/inf_int.h"
#include "Expr.h"
#include "NumberExpr.h"
#include "VariableExpr.h"
#include "BinaryExpr.h"
#include <sstream>
#include <stdexcept>
#include <cmath>

// ax + b 형태
struct LinearForm {
    double a;
    double b;
};

class Evaluator {
public:
    static double infIntToDouble(const inf_int& v);
    static LinearForm evalLinear(Expr* e);
};
