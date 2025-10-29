#include "../include2/EquationSolverService.h"
#include "../include2/Parser.h"
#include "../include2/Evaluator.h"
#include <sstream>
#include <stdexcept>
#include <cmath>

double EquationSolverService::infIntToDouble(const inf_int& v) {
    return Evaluator::infIntToDouble(v);
}

LinearForm EquationSolverService::evalLinear(Expr* e) {
    return Evaluator::evalLinear(e);
}

void EquationSolverService::deleteExpr(Expr* e) {
    delete e; // BinaryExpr::~BinaryExpr()가 자식까지 지움
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
