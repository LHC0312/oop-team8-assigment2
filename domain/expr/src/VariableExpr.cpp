#include "../include2/VariableExpr.h"

VariableExpr::VariableExpr(const std::string& n)
    : name(n)
{}

inf_int VariableExpr::evaluate(const std::string& varName,
                               const inf_int& varValue) const {
    if (name == varName)
        return varValue;

    // 다른 변수는 0으로 처리 (또는 throw 가능)
    return inf_int(0);
}
