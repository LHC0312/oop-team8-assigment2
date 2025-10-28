#pragma once
#include <string>
#include "../../include/inf_int.h"


class Expr {
public:
    virtual ~Expr();

    virtual inf_int evaluate(const std::string& varName,
                             const inf_int& varValue) const = 0;
};

enum class BinaryOp {
    Add, 
    Sub, 
    Mul  
};
