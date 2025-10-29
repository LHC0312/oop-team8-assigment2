#include "../include2/Evaluator.h"

double Evaluator::infIntToDouble(const inf_int& v) {
    std::ostringstream oss;
    oss << v;
    return std::stold(oss.str());
}

LinearForm Evaluator::evalLinear(Expr* e) {
    // NumberExpr -> 상수항 b만 존재: 0*x + b
    if (auto num = dynamic_cast<NumberExpr*>(e)) {
        return LinearForm{
            0.0,
            infIntToDouble(num->getValue())
        };
    }

    // VariableExpr -> x라고 가정: 1*x + 0
    if (auto var = dynamic_cast<VariableExpr*>(e)) {
        (void)var; // 이름은 "x" 하나만 취급한다고 가정
        return LinearForm{
            1.0,
            0.0
        };
    }

    // BinaryExpr -> 왼쪽/오른쪽을 해석해서 결합
    if (auto bin = dynamic_cast<BinaryExpr*>(e)) {
        LinearForm L = evalLinear(bin->getLeft());
        LinearForm R = evalLinear(bin->getRight());

        switch (bin->getOp()) {
            case BinaryOp::Add:
                return LinearForm{
                    L.a + R.a,
                    L.b + R.b
                };
            case BinaryOp::Sub:
                return LinearForm{
                    L.a - R.a,
                    L.b - R.b
                };
            case BinaryOp::Mul:
                // (a1*x + b1)*(a2*x + b2)
                // = (a1*b2 + a2*b1)*x + (b1*b2)
                // 단 a1*a2 != 0면 x^2 항 생김 -> 비선형 -> 에러
                if ((L.a != 0.0) && (R.a != 0.0)) {
                    throw std::runtime_error("Non-linear term detected (x*x). Only linear equations supported.");
                }

            {
                double newA = L.a * R.b + R.a * L.b;
                double newB = L.b * R.b;
                return LinearForm{
                    newA,
                    newB
                };
            }
            default:
                throw std::runtime_error("Unknown binary operator in evalLinear");
        }
    }

    throw std::runtime_error("Unsupported expression node in evalLinear");
}
