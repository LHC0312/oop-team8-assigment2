#pragma once
#include <string>
#include "../../include/inf_int.h"
#include "Expr.h"
#include "NumberExpr.h"
#include "VariableExpr.h"
#include "BinaryExpr.h"

// Parser: 문자열 -> AST(Expr*)
class Parser {
private:
    std::string s;
    size_t pos;

    char peek() const;
    char get();
    void skipSpaces();

    Expr* parseNumber();
    Expr* parseVariable();
    Expr* parseFactor(); // unary -
    Expr* parseTerm();   // *
    Expr* parseExpr();   // +, -

public:
    Parser(const std::string& input);
    Expr* parse();
};
