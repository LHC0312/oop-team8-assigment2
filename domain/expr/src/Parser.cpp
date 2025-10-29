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
    if (c == '(') {
            get(); // '(' 소모
            Expr* node = parseExpr(); // 괄호 안의 표현식을 파싱
            skipSpaces();
            if (peek() != ')') {
                std::string error_msg = "Breaktheses not exist";
                error_msg.push_back(c);
                throw std::runtime_error(error_msg);
            }
            get(); // ')' 소모
            return node;
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
Expr* Parser::parsePower() {
    Expr* node = parseFactor(); // 왼쪽 피연산자(base)
    skipSpaces();
    if (peek() == '^') {
        get(); // '^' 소모
        Expr* right = parsePower(); // <--- 오른쪽 피연산자(exponent)를 재귀적으로 파싱
        node = new BinaryExpr(BinaryOp::Pow, node, right);
    }
    return node;
}
Expr* Parser::parseTerm() {
    Expr* node = parsePower();
    while (true) {
        skipSpaces();
        char c = peek();
        if (c == '*') {
            get();
            Expr* right = parsePower();
            node = new BinaryExpr(BinaryOp::Mul, node, right);
        } else if(c == '/'){
            get();
            Expr* right = parsePower();
            node = new BinaryExpr(BinaryOp::Div, node, right);
        }else if (c == '%') { // <--- MOD (%) 처리 추가
            get();
            Expr* right = parsePower();
            node = new BinaryExpr(BinaryOp::Mod, node, right);
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
