#include "../include2/VariableExpr.h"

VariableExpr::VariableExpr(const std::string& n)
    : name(n)
{}

inf_int VariableExpr::evaluate(const std::string& varName,
                               const inf_int& varValue) const {
    if (name == varName)
        return varValue;

    return inf_int(0);
}
