#pragma once
#include "Expr.h"

class NumberExpr : public Expr {
private:
    inf_int value;

public:
    NumberExpr(const inf_int& v);
    virtual inf_int evaluate(const std::string& varName,
                             const inf_int& varValue) const override;
};
