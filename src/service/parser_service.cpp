#include "parse.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <stack>

using namespace std;

// Default constructor
ParserService::ParserService() : s(""), pos(0) {
}

// Legacy constructor for backward compatibility
ParserService::ParserService(const string& input) : s(input), pos(0) {
}

char ParserService::peek() const {
  if (pos < s.size()) return s[pos];
  return '\0';
}

char ParserService::get() const {
  if (pos < s.size()) return s[pos++];
  return '\0';
}

void ParserService::skipSpaces() const {
  while (std::isspace(static_cast<unsigned char>(peek()))) {
    get();
  }
}

inf_int* ParserService::parseNumber() const {
  std::string numStr;
  while (std::isdigit(static_cast<unsigned char>(peek()))) {
    numStr.push_back(get());
  }
  if (numStr.empty()) {
    throw std::runtime_error("Expected number");
  }
  return new inf_int(numStr.c_str());
}

Variable* ParserService::parseVariable() const {
  std::string name;
  while (std::isalpha(static_cast<unsigned char>(peek()))) {
    name.push_back(get());
  }
  if (name.empty()) {
    throw std::runtime_error("Expected variable name");
  }
  return new Variable();
}

// Main service method: string → vector<Token>
vector<Token> ParserService::tokenize(const string& expression) const {
    vector<Token> tokens;
    s = expression;
    pos = 0;
    
    while (pos < s.length()) {
        skipSpaces();
        if (pos >= s.length()) break;
        
        char c = peek();
        
        if (isdigit(c) || (c == '-' && tokens.empty()) || 
            (c == '-' && !tokens.empty() && 
             (tokens.back().type == TokenType::LEFT_PAREN || tokens.back().type == TokenType::OPERATOR))) {
            // Parse number (including negative numbers)
            string numStr;
            if (c == '-') {
                numStr += get();
            }
            while (pos < s.length() && isdigit(peek())) {
                numStr += get();
            }
            tokens.emplace_back(TokenType::NUMBER, numStr);
            
        } else if (isalpha(c)) {
            // Parse variable
            string varStr;
            while (pos < s.length() && isalpha(peek())) {
                varStr += get();
            }
            if (variableHandler.isVariable(varStr)) {
                tokens.emplace_back(TokenType::VARIABLE, varStr);
            } else {
                throw runtime_error("Unknown variable: " + varStr);
            }
            
        } else if (operatorManager.isOperator(string(1, c))) {
            // Parse operator
            tokens.emplace_back(TokenType::OPERATOR, string(1, get()));
            
        } else if (c == '(') {
            tokens.emplace_back(TokenType::LEFT_PAREN, string(1, get()));
            
        } else if (c == ')') {
            tokens.emplace_back(TokenType::RIGHT_PAREN, string(1, get()));
            
        } else {
            throw runtime_error("Invalid character: " + string(1, c));
        }
    }
    
    return tokens;
}

// Convert infix tokens to postfix using Shunting Yard algorithm
vector<Token> ParserService::infixToPostfix(const vector<Token>& tokens) const {
    vector<Token> output;
    stack<Token> operators;
    
    for (const auto& token : tokens) {
        switch (token.type) {
            case TokenType::NUMBER:
            case TokenType::VARIABLE:
                output.push_back(token);
                break;
                
            case TokenType::LEFT_PAREN:
                operators.push(token);
                break;
                
            case TokenType::RIGHT_PAREN:
                while (!operators.empty() && operators.top().type != TokenType::LEFT_PAREN) {
                    output.push_back(operators.top());
                    operators.pop();
                }
                if (operators.empty()) {
                    throw runtime_error("Mismatched parentheses");
                }
                operators.pop(); // Remove left parenthesis
                break;
                
            case TokenType::OPERATOR: {
                // Get precedence from OperatorManager (we'll add this method)
                int prec1 = getOperatorPrecedence(token.value);
                
                while (!operators.empty() && operators.top().type == TokenType::OPERATOR) {
                    int prec2 = getOperatorPrecedence(operators.top().value);
                    
                    // Right associative for ^ operator
                    bool isRightAssoc = (token.value == "^");
                    if ((!isRightAssoc && prec2 >= prec1) || (isRightAssoc && prec2 > prec1)) {
                        output.push_back(operators.top());
                        operators.pop();
                    } else {
                        break;
                    }
                }
                operators.push(token);
                break;
            }
        }
    }
    
    while (!operators.empty()) {
        if (operators.top().type == TokenType::LEFT_PAREN || operators.top().type == TokenType::RIGHT_PAREN) {
            throw runtime_error("Mismatched parentheses");
        }
        output.push_back(operators.top());
        operators.pop();
    }
    
    return output;
}

bool ParserService::hasVariables(const vector<Token>& tokens) const {
    for (const auto& token : tokens) {
        if (token.type == TokenType::VARIABLE) {
            return true;
        }
    }
    return false;
}

// Helper method for operator precedence
int ParserService::getOperatorPrecedence(const string& op) const {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

