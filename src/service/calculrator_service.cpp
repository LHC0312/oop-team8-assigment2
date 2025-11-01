#include "calculator_service.h"
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Constructor to initialize domain objects
CalculatorService::CalculatorService() : parser(), operatorManager(), variableHandler() {
}


string CalculatorService::evaluateExpression(const string& expression) const {
    try {
        if (expression == "0" || expression == "q" || expression == "Q" || expression.empty()) {
            return "EXIT";
        }
        
        // Use ParserService for tokenization and conversion
        const auto tokens = parser.tokenize(expression);
        if (tokens.empty()) {
            return "EXIT";
        }
        
        const auto postfix = parser.infixToPostfix(tokens);
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
        } else if (isOperator(string(1, c)) || c == '(' || c == ')') {
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
        if (isNumber(token) || isVariable(token)) {
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
                   ((token != "^" && getPrecedence(operators.top()) >= getPrecedence(token)) ||
                    (token == "^" && getPrecedence(operators.top()) > getPrecedence(token)))) {
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


bool CalculatorService::isNumber(const string& token) const {
    if (token.empty()) return false;
    
    size_t start = 0;
    if (token[0] == '-') {
        start = 1;
        if (token.length() == 1) return false;
    }
    
    return all_of(token.begin() + start, token.end(), 
                  [](char c) { return isdigit(c); });
}

bool CalculatorService::isOperator(const string& token) const {
    if (token.empty()) return false;

    if (token == "-" || token == "+" || token == "*" || token == "/" || token == "^") {
        return true;
    }
    return false;
}

int CalculatorService::getPrecedence(const string& op) const {
    if (op == "+" || op == "-") {
        return 1;
    } else if (op == "*" || op == "/") {
        return 2;
    } else if (op == "^") {
        return 3;
    }
    return 0;
}

bool CalculatorService::isVariable(const string& token) const {
    return token == "x" || token == "X";
}

bool CalculatorService::hasVariables(const string& expression) const {
    try {
        const auto tokens = parser.tokenize(expression);
        return parser.hasVariables(tokens);
    } catch (const exception&) {
        return false;
    }
}

string CalculatorService::evaluateExpressionWithVariables(const string& expression, const unordered_map<string, double>& variables) const {
    try {
        if (expression == "0" || expression == "q" || expression == "Q" || expression.empty()) {
            return "EXIT";
        }
        
        // Use ParserService for tokenization and conversion
        const auto tokens = parser.tokenize(expression);
        if (tokens.empty()) {
            return "EXIT";
        }
        
        const auto postfix = parser.infixToPostfix(tokens);
        const auto result = evaluatePostfixWithVariables(postfix, variables);
        
        ostringstream oss;
        oss << result;
        return oss.str();
    } catch (const exception& e) {
        return string("Error: ") + e.what();
    }
}

// New Token-based evaluation methods using domain classes
inf_int CalculatorService::evaluatePostfix(const vector<Token>& postfix) const {
    stack<inf_int> operandStack;
    
    for (const auto& token : postfix) {
        switch (token.type) {
            case TokenType::NUMBER:
                operandStack.emplace(token.value.c_str());
                break;
                
            case TokenType::VARIABLE:
                throw runtime_error("Variable '" + token.value + "' found but no values provided");
                
            case TokenType::OPERATOR: {
                if (operandStack.size() < 2) {
                    throw runtime_error("Invalid expression");
                }
                
                const auto b = operandStack.top();
                operandStack.pop();
                const auto a = operandStack.top();
                operandStack.pop();
                
                // Use OperatorManager for calculation
                const auto result = operatorManager.execute(token.value, a, b);
                operandStack.push(result);
                break;
            }
            
            default:
                throw runtime_error("Invalid token type in postfix expression");
        }
    }
    
    if (operandStack.size() != 1) {
        throw runtime_error("Invalid expression");
    }
    
    return operandStack.top();
}

inf_int CalculatorService::evaluatePostfixWithVariables(const vector<Token>& postfix, const unordered_map<string, double>& variables) const {
    stack<inf_int> operandStack;
    
    for (const auto& token : postfix) {
        switch (token.type) {
            case TokenType::NUMBER:
                operandStack.emplace(token.value.c_str());
                break;
                
            case TokenType::VARIABLE: {
                string lowerToken = token.value;
                transform(lowerToken.begin(), lowerToken.end(), lowerToken.begin(), ::tolower);
                auto it = variables.find(lowerToken);
                if (it == variables.end()) {
                    throw runtime_error("Variable '" + token.value + "' not found");
                }
                operandStack.emplace(static_cast<int>(it->second));
                break;
            }
            
            case TokenType::OPERATOR: {
                if (operandStack.size() < 2) {
                    throw runtime_error("Invalid expression");
                }
                
                const auto b = operandStack.top();
                operandStack.pop();
                const auto a = operandStack.top();
                operandStack.pop();
                
                // Use OperatorManager for calculation
                const auto result = operatorManager.execute(token.value, a, b);
                operandStack.push(result);
                break;
            }
            
            default:
                throw runtime_error("Invalid token type in postfix expression");
        }
    }
    
    if (operandStack.size() != 1) {
        throw runtime_error("Invalid expression");
    }
    
    return operandStack.top();
}
