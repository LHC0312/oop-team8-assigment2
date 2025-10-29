#pragma once
#include "Expr.h"
#include <string>

class VariableExpr : public Expr {
private:
    std::string name;
public:
    VariableExpr(const std::string& n) : name(n) {}
    const std::string& getName() const { return name; }
};
