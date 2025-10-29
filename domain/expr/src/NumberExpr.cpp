#include "../include2/NumberExpr.h"

NumberExpr::NumberExpr(const inf_int& v)
    : value(v)
{}

inf_int NumberExpr::evaluate(const std::string&, const inf_int&) const {
    return value;
}
