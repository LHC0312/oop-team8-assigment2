//
// Created by 이해찬 on 2025. 10. 30..
//

#ifndef PARSE_H
#define PARSE_H

#include "inf_int.h"
#include "variable.h"
#include "operatorManager.h"
#include <string>
#include <vector>

using namespace std;

// Token types for parsing
enum class TokenType {
    NUMBER,
    VARIABLE,
    OPERATOR,
    LEFT_PAREN,
    RIGHT_PAREN
};

struct Token {
    TokenType type;
    string value;
    
    Token(TokenType t, const string& v) : type(t), value(v) {}
};

class ParserService {
  private:
    mutable string s;
    mutable int pos;
    OperatorManager operatorManager;
    Variable variableHandler;
    
    char peek() const;
    char get() const;
    void skipSpaces() const;
    inf_int* parseNumber() const;
    Variable* parseVariable() const;
    int getOperatorPrecedence(const string& op) const;
    
  public:
    ParserService();
    
    // Main service methods
    vector<Token> tokenize(const string& expression) const;
    vector<Token> infixToPostfix(const vector<Token>& tokens) const;
    bool hasVariables(const vector<Token>& tokens) const;
    
    // Legacy Parser methods for backward compatibility
    ParserService(const string& input);
};

// Type alias for backward compatibility
using Parser = ParserService;

#endif //PARSE_H
