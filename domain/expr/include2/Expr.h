#pragma once
#include <string>
#include "../../include/inf_int.h"


class Expr {
public:
    virtual ~Expr();

    virtual inf_int evaluate(const std::string& varName,
                             const inf_int& varValue) const = 0;
    virtual bool isEquation() const { //방정식인지 판단
        return false;
    }
};

enum class BinaryOp {
    Add, 
    Sub, 
    Mul,
    Div,
    Pow,
    Mod,
    Equal
};
