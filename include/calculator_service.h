#ifndef CALCULATOR_SERVICE_H
#define CALCULATOR_SERVICE_H

#include "inf_int.h"
#include "operator.h"
#include <string>
#include <vector>

using namespace std;

class CalculatorService {
public:
    CalculatorService() = default;
    ~CalculatorService() = default;
    
    string evaluateExpression(const string& expression) const;

private:
    vector<string> tokenize(const string& expression) const;
    vector<string> infixToPostfix(const vector<string>& tokens) const;
    inf_int evaluatePostfix(const vector<string>& postfix) const;
    
    static bool isNumber(const string& token);
};

#endif