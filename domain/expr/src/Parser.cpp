#include "../include2/Parser.h"
#include <cctype>
#include <stdexcept>

Parser::Parser(const std::string& input)
    : s(input), pos(0) {}

char Parser::peek() const {
    if (pos < s.size()) return s[pos];
    return '\0';
}

char Parser::get() {
    if (pos < s.size()) return s[pos++];
    return '\0';
}

void Parser::skipSpaces() {
    while (std::isspace(static_cast<unsigned char>(peek()))) {
        get();
    }
}

Expr* Parser::parseNumber() {
    std::string numStr;
    while (std::isdigit(static_cast<unsigned char>(peek()))) {
        numStr.push_back(get());
    }
    if (numStr.empty()) {
        throw std::runtime_error("Expected number");
    }
    return new NumberExpr(inf_int(numStr.c_str()));
}

Expr* Parser::parseVariable() {
    std::string name;
    while (std::isalpha(static_cast<unsigned char>(peek()))) {
        name.push_back(get());
    }
    if (name.empty()) {
        throw std::runtime_error("Expected variable name");
    }
    return new VariableExpr(name);
}

// Factor :=
//    '-' Factor        (단항 음수는 (0 - Factor))
//  | Number
//  | Variable
Expr* Parser::parseFactor() {
    skipSpaces();
    char c = peek();

    if (c == '-') {
        get(); // consume '-'
        Expr* zero = new NumberExpr(inf_int(0));
        Expr* rhs  = parseFactor();
        return new BinaryExpr(BinaryOp::Sub, zero, rhs);
    }

    if (std::isdigit(static_cast<unsigned char>(c))) {
        return parseNumber();
    }

    if (std::isalpha(static_cast<unsigned char>(c))) {
        return parseVariable();
    }

    throw std::runtime_error("Unexpected token in factor");
}

// Term := Factor ( '*' Factor )*
Expr* Parser::parseTerm() {
    Expr* node = parseFactor();
    while (true) {
        skipSpaces();
        char c = peek();
        if (c == '*') {
            get(); // consume '*'
            Expr* right = parseFactor();
            node = new BinaryExpr(BinaryOp::Mul, node, right);
        } else {
            break;
        }
    }
    return node;
}

// Expr := Term ( ('+' | '-') Term )*
Expr* Parser::parseExpr() {
    Expr* node = parseTerm();
    while (true) {
        skipSpaces();
        char c = peek();
        if (c == '+') {
            get(); // consume '+'
            Expr* right = parseTerm();
            node = new BinaryExpr(BinaryOp::Add, node, right);
        } else if (c == '-') {
            get(); // consume '-'
            Expr* right = parseTerm();
            node = new BinaryExpr(BinaryOp::Sub, node, right);
        } else {
            break;
        }
    }
    return node;
}

Expr* Parser::parse() {
    Expr* root = parseExpr();
    skipSpaces();
    return root;
}
