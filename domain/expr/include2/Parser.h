#pragma once
#include <string>
#include <cctype>
#include "Expr.h"
#include "NumberExpr.h"
#include "VariableExpr.h"
#include "BinaryExpr.h"

class Parser {
private:
    std::string s;
    size_t pos;

    char peek() const;
    char get();
    void skipSpaces();

    Expr* parseNumber();
    Expr* parseVariable();
    Expr* parseFactor();
    Expr* parseTerm();
    Expr* parsePower();
    Expr* parseEquation();
    Expr* parseExpr();

public:
    Parser(const std::string& input);
    Expr* parse();
};
