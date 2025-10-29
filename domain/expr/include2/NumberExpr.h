#pragma once
#include "Expr.h"
#include "../../include/inf_int.h"

class NumberExpr : public Expr {
private:
    inf_int value;
public:
    NumberExpr(const inf_int& v) : value(v) {}
    const inf_int& getValue() const { return value; }
};
