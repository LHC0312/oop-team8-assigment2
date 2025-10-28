#pragma once
#include "Expr.h"

class BinaryExpr : public Expr {
private:
    BinaryOp op;
    Expr* left;
    Expr* right;

public:
    BinaryExpr(BinaryOp o, Expr* l, Expr* r);
    virtual ~BinaryExpr();

    virtual inf_int evaluate(const std::string& varName,
                             const inf_int& varValue) const override;
};
