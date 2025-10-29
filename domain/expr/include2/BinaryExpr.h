#pragma once
#include "Expr.h"
using namespace std;

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
    BinaryOp getOp() const { return op; }
    Expr* getLeft() const { return left; }
    Expr* getRight() const { return right; }
};

