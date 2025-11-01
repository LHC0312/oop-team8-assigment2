#ifndef CALCULATOR_SERVICE_H
#define CALCULATOR_SERVICE_H

#include "inf_int.h"
#include "parse.h"
#include "operatorManager.h"
#include "variable.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class CalculatorService {
public:
    CalculatorService();
    ~CalculatorService() = default;
    
    string evaluateExpression(const string& expression) const;
    string evaluateExpressionWithVariables(const string& expression, const unordered_map<string, double>& variables) const;
    bool hasVariables(const string& expression) const;

private:
    ParserService parser;
    OperatorManager operatorManager;
    Variable variableHandler;
    
    // Updated methods to use Token-based approach
    inf_int evaluatePostfix(const vector<Token>& postfix) const;
    inf_int evaluatePostfixWithVariables(const vector<Token>& postfix, const unordered_map<string, double>& variables) const;
    
    // Legacy methods for backward compatibility (deprecated)
    vector<string> tokenize(const string& expression) const;
    vector<string> infixToPostfix(const vector<string>& tokens) const;
    bool isOperator(const string& token) const;
    bool isNumber(const string& token) const;
    bool isVariable(const string& token) const;
    int getPrecedence(const string& op) const;
};

#endif