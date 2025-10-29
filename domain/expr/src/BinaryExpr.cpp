#include "../include2/BinaryExpr.h"

BinaryExpr::BinaryExpr(BinaryOp o, Expr* l, Expr* r)
    : op(o), left(l), right(r)
{}

BinaryExpr::~BinaryExpr() {
    delete left;
    delete right;
}

inf_int BinaryExpr::evaluate(const std::string& varName,
                             const inf_int& varValue) const {
    inf_int lv = left->evaluate(varName, varValue);
    inf_int rv = right->evaluate(varName, varValue);

    switch (op) {
        case BinaryOp::Add:
            return lv + rv;
        case BinaryOp::Sub:
            return lv - rv;
        case BinaryOp::Mul:
            return lv * rv;
    }

    return inf_int(0); // safety fallback
}
