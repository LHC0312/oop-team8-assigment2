#include "EquationSolverService.h"
#include <limits>
#include <typeinfo>
#include <sstream>
#include <stdexcept>
#include <cmath>

double EquationSolverService::infIntToDouble(const inf_int& v) {
    // inf_int를 문자열로 바꾸고 그걸 long double로 변환한 뒤 double로 저장
    std::ostringstream oss;
    oss << v;
    return std::stold(oss.str());
}

LinearForm EquationSolverService::evalLinear(Expr* e) {
    // 상수 노드인 경우
    if (auto num = dynamic_cast<NumberExpr*>(e)) {
        // c == 0*x + c
        return LinearForm{
            0.0,
            infIntToDouble(num->getValue())
        };
    }

    if (auto var = dynamic_cast<VariableExpr*>(e)) {
        return LinearForm{
            1.0,
            0.0
        };
    }

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

void EquationSolverService::deleteExpr(Expr* e) {
    delete e;
}


std::string EquationSolverService::solveEquationLine(const std::string& line) {
    size_t eqPos = line.find('=');
    if (eqPos == std::string::npos) {
        throw std::runtime_error("No '=' found in equation.");
    }

    std::string leftStr  = line.substr(0, eqPos);
    std::string rightStr = line.substr(eqPos + 1);

    Parser pL(leftStr);
    Expr* leftExpr = pL.parse();

    Parser pR(rightStr);
    Expr* rightExpr = pR.parse();

    LinearForm L = evalLinear(leftExpr);
    LinearForm R = evalLinear(rightExpr);

    double A = L.a - R.a;
    double B = L.b - R.b;

    const double EPS = 1e-12;
    std::ostringstream out;
    if (std::fabs(A) < EPS) {
        if (std::fabs(B) < EPS) {
            out << "해가 무한히 많습니다.";
        } else {
            out << "해가 존재하지 않습니다.";
        }
    } else {
        double xval = -B / A;
        out << "x = " << xval;
    }

    deleteExpr(leftExpr);
    deleteExpr(rightExpr);

    return out.str();
}
