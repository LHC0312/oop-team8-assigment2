#include "../include2/Parser.h"

Parser::Parser(const std::string& input)
    : s(input), pos(0)
{}

char Parser::peek() const {
    if (pos < s.size()) return s[pos];
    return '\0';
}

char Parser::get() {
    if (pos < s.size()) return s[pos++];
    return '\0';
}

void Parser::skipSpaces() {
    while (std::isspace((unsigned char)peek())) {
        get();
    }
}

Expr* Parser::parseNumber() {
    std::string numStr;
    while (std::isdigit((unsigned char)peek())) {
        numStr.push_back(get());
    }
    inf_int val(numStr.c_str());
    return new NumberExpr(val);
}

Expr* Parser::parseVariable() {
    std::string name;
    while (std::isalpha((unsigned char)peek())) {
        name.push_back(get());
    }
    return new VariableExpr(name);
}

Expr* Parser::parseFactor() {
    skipSpaces();
    char c = peek();

    // 단항 음수 처리: -Factor → (0 - Factor)
    if (c == '-') {
        get();
        Expr* zero = new NumberExpr(inf_int(0));
        Expr* rhs = parseFactor();
        return new BinaryExpr(BinaryOp::Sub, zero, rhs);
    }

    if (std::isdigit((unsigned char)c)) {
        return parseNumber();
    } else if (std::isalpha((unsigned char)c)) {
        return parseVariable();
    } else {
        get(); // 예외 문자 스킵
        return new NumberExpr(inf_int(0));
    }
}

Expr* Parser::parseTerm() {
    Expr* node = parseFactor();
    while (true) {
        skipSpaces();
        char c = peek();
        if (c == '*') {
            get();
            Expr* right = parseFactor();
            node = new BinaryExpr(BinaryOp::Mul, node, right);
        } else {
            break;
        }
    }
    return node;
}

Expr* Parser::parseExpr() {
    Expr* node = parseTerm();
    while (true) {
        skipSpaces();
        char c = peek();
        if (c == '+') {
            get();
            Expr* right = parseTerm();
            node = new BinaryExpr(BinaryOp::Add, node, right);
        } else if (c == '-') {
            get();
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
