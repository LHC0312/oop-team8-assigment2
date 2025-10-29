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
        // �θ�(Expr)�� �Լ��� ������(override)
        return op == BinaryOp::Equal;
    }
    /**
     * @brief �������� Ǯ �� ��/�캯�� �����ϱ� ���� ����(getter) �Լ���
     */
    Expr* getLeft() const {
        return left;
    }
    
    Expr* getRight() const {
        return right;
    }
};
