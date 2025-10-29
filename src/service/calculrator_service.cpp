#include "../include/calculator_service.h"
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cctype>

CalculatorService::CalculatorService() {}

std::string CalculatorService::evaluateExpression(const std::string& expression) {
    try {
        if (expression == "0") {
            return "EXIT";
        }
        
        std::vector<std::string> tokens = tokenize(expression);
        if (tokens.empty()) {
            throw std::runtime_error("Empty expression");
        }
        
        std::vector<std::string> postfix = infixToPostfix(tokens);
        inf_int result = evaluatePostfix(postfix);
        
        std::ostringstream oss;
        oss << result;
        return oss.str();
    } catch (const std::exception& e) {
        return std::string("Error: ") + e.what();
    }
}

std::vector<std::string> CalculatorService::tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    std::string current;
    
    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];
        
        if (std::isspace(c)) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '(' || c == ')') {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
            
            if (c == '-' && (tokens.empty() || tokens.back() == "(" || isOperator(tokens.back()))) {
                current += c;
            } else {
                tokens.push_back(std::string(1, c));
            }
        } else {
            current += c;
        }
    }
    
    if (!current.empty()) {
        tokens.push_back(current);
    }
    
    return tokens;
}

std::vector<std::string> CalculatorService::infixToPostfix(const std::vector<std::string>& tokens) {
    std::vector<std::string> output;
    std::stack<std::string> operators;
    
    for (const std::string& token : tokens) {
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
                throw std::runtime_error("Mismatched parentheses");
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
            throw std::runtime_error("Invalid token: " + token);
        }
    }
    
    while (!operators.empty()) {
        if (operators.top() == "(" || operators.top() == ")") {
            throw std::runtime_error("Mismatched parentheses");
        }
        output.push_back(operators.top());
        operators.pop();
    }
    
    return output;
}

inf_int CalculatorService::evaluatePostfix(const std::vector<std::string>& postfix) {
    std::stack<inf_int> stack;
    
    for (const std::string& token : postfix) {
        if (isNumber(token)) {
            stack.push(inf_int(token.c_str()));
        } else if (isOperator(token)) {
            if (stack.size() < 2) {
                throw std::runtime_error("Invalid expression");
            }
            
            inf_int b = stack.top(); stack.pop();
            inf_int a = stack.top(); stack.pop();
            
            if (token == "+") {
                stack.push(a + b);
            } else if (token == "-") {
                stack.push(a - b);
            } else if (token == "*") {
                stack.push(a * b);
            } else {
                throw std::runtime_error("Unknown operator: " + token);
            }
        }
    }
    
    if (stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }
    
    return stack.top();
}

int CalculatorService::precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*") return 2;
    return 0;
}

bool CalculatorService::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*";
}

bool CalculatorService::isNumber(const std::string& token) {
    if (token.empty()) return false;
    
    size_t start = 0;
    if (token[0] == '-') {
        start = 1;
        if (token.length() == 1) return false;
    }
    
    for (size_t i = start; i < token.length(); i++) {
        if (!std::isdigit(token[i])) {
            return false;
        }
    }
    
    return true;
}
