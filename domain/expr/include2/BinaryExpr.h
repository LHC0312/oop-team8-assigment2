#pragma once
#include "Expr.h"

enum class BinaryOp {
    Add,
    Sub,
    Mul
};

class BinaryExpr : public Expr {
private:
    BinaryOp op;
    Expr* left;
    Expr* right;

public:
    BinaryExpr(BinaryOp o, Expr* l, Expr* r)
        : op(o), left(l), right(r) {}

    ~BinaryExpr() {
        // 우린 EquationSolverService에서 수동으로 delete 안 하고
        // 여기서 소유권 정리하도록 한다.
        delete left;
        delete right;
    }

    BinaryOp getOp() const { return op; }
    Expr*    getLeft() const { return left; }
    Expr*    getRight() const { return right; }
};
