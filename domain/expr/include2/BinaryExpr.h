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
    virtual bool isEquation() const override {
        // 부모(Expr)의 함수를 재정의(override)
        return op == BinaryOp::Equal;
    }
    /**
     * @brief 방정식을 풀 때 좌/우변에 접근하기 위한 헬퍼(getter) 함수들
     */
    Expr* getLeft() const {
        return left;
    }
    
    Expr* getRight() const {
        return right;
    }
};
