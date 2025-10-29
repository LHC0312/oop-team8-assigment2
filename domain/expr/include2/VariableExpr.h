#pragma once
#include "Expr.h"

class VariableExpr : public Expr {
private:
    std::string name;

public:
    VariableExpr(const std::string& n);
    virtual inf_int evaluate(const std::string& varName,
                             const inf_int& varValue) const override;
};
