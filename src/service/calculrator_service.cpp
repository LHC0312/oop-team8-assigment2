#include "../include/calculator_service.h"
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <utility>

using namespace std;

string CalculatorService::evaluateExpression(const string& expression) const {
    try {
        if (expression == "0") {
            return "EXIT";
        }
        
        const auto tokens = tokenize(expression);
        if (tokens.empty()) {
            throw runtime_error("Empty expression");
        }
        
        const auto postfix = infixToPostfix(tokens);
        const auto result = evaluatePostfix(postfix);
        
        ostringstream oss;
        oss << result;
        return oss.str();
    } catch (const exception& e) {
        return string("Error: ") + e.what();
    }
}

vector<string> CalculatorService::tokenize(const string& expression) const {
    vector<string> tokens;
    string current;
    
    for (size_t i = 0; i < expression.length(); ++i) {
        const char c = expression[i];
        
        if (isspace(c)) {
            if (!current.empty()) {
                tokens.push_back(std::move(current));
                current.clear();
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '(' || c == ')') {
            if (!current.empty()) {
                tokens.push_back(std::move(current));
                current.clear();
            }
            
            if (c == '-' && (tokens.empty() || tokens.back() == "(" || isOperator(tokens.back()))) {
                current += c;
            } else {
                tokens.emplace_back(1, c);
            }
        } else {
            current += c;
        }
    }
    
    if (!current.empty()) {
        tokens.push_back(std::move(current));
    }
    
    return tokens;
}

vector<string> CalculatorService::infixToPostfix(const vector<string>& tokens) const {
    vector<string> output;
    stack<string> operators;
    
    for (const auto& token : tokens) {
        if (isNumber(token)) {
            output.push_back(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                output.push_back(operators.top());
                operators.pop();
            }
            if (operators.empty()) {
                throw runtime_error("Mismatched parentheses");
            }
            operators.pop();
        } else if (isOperator(token)) {
            while (!operators.empty() && operators.top() != "(" &&
                   precedence(operators.top()) >= precedence(token)) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        } else {
            throw runtime_error("Invalid token: " + token);
        }
    }
    
    while (!operators.empty()) {
        if (operators.top() == "(" || operators.top() == ")") {
            throw runtime_error("Mismatched parentheses");
        }
        output.push_back(operators.top());
        operators.pop();
    }
    
    return output;
}

inf_int CalculatorService::evaluatePostfix(const vector<string>& postfix) const {
    stack<inf_int> operandStack;
    
    for (const auto& token : postfix) {
        if (isNumber(token)) {
            operandStack.emplace(token.c_str());
        } else if (isOperator(token)) {
            if (operandStack.size() < 2) {
                throw runtime_error("Invalid expression");
            }
            
            const auto b = operandStack.top(); 
            operandStack.pop();
            const auto a = operandStack.top(); 
            operandStack.pop();
            
            if (token == "+") {
                operandStack.push(a + b);
            } else if (token == "-") {
                operandStack.push(a - b);
            } else if (token == "*") {
                operandStack.push(a * b);
            } else {
                throw runtime_error("Unknown operator: " + token);
            }
        }
    }
    
    if (operandStack.size() != 1) {
        throw runtime_error("Invalid expression");
    }
    
    return operandStack.top();
}

int CalculatorService::precedence(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*") return 2;
    return 0;
}

bool CalculatorService::isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*";
}

bool CalculatorService::isNumber(const string& token) {
    if (token.empty()) return false;
    
    size_t start = 0;
    if (token[0] == '-') {
        start = 1;
        if (token.length() == 1) return false;
    }
    
    return all_of(token.begin() + start, token.end(), 
                  [](char c) { return isdigit(c); });
}
