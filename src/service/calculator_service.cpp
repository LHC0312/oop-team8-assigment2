#include "../include/calculator_service.h"
#include <sstream>  // std::ostringstream을 위해
#include <stack>    // std::stack을 위해
#include <stdexcept> // std::runtime_error를 위해
#include <cctype>   // std::isspace, std::isdigit을 위해

/**
 * @brief 메인 함수: 문자열 형태의 중위 표기법 식을 받아 계산하고, 결과를 문자열로 반환합니다.
 * @param expression 사용자가 입력한 산술 식 (예: "10 + (5 * -2)")
 * @return 계산 결과 문자열. "0" 입력 시 "EXIT", 오류 발생 시 "Error: ..." 반환
 */
std::string CalculatorService::evaluateExpression(const std::string& expression) const{
    try {
        // "0"은 종료 명령으로 처리
        if (expression == "0") {
            return "EXIT";
        }
        
        // 1. 토큰화: "10 + 5" -> {"10", "+", "5"}
        std::vector<std::string> tokens = tokenize(expression);
        if (tokens.empty()) {
            throw std::runtime_error("Empty expression");
        }
        
        // 2. 중위 -> 후위 변환 (샤일링 야드): {"10", "+", "5"} -> {"10", "5", "+"}
        std::vector<std::string> postfix = infixToPostfix(tokens);
        
        // 3. 후위 표기법 계산: {"10", "5", "+"} -> 15
        inf_int result = evaluatePostfix(postfix);
        
        // 4. inf_int 결과를 문자열로 변환하여 반환
        std::ostringstream oss;
        oss << result;
        return oss.str();
    } catch (const std::exception& e) {
        // 모든 예외를 잡아서 오류 메시지로 반환
        return std::string("Error: ") + e.what();
    }
}

/**
 * @brief 문자열 식을 토큰(단어) 단위로 분리합니다.
 * @param expression "10 + (5 * -2)"
 * @return {"10", "+", "(", "5", "*", "-2", ")"}
 */
std::vector<std::string> CalculatorService::tokenize(const std::string& expression) const{
    std::vector<std::string> tokens;
    std::string current; // 현재 만들고 있는 토큰 (숫자 또는 음수)
    
    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];
        
        // 1. 공백: 현재 토큰(current)이 있다면 저장하고 비움
        if (std::isspace(c)) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        // 2. 연산자 또는 괄호
        } else if (c == '+' || c == '-' || c == '*' || c == '(' || c == ')' || c == '/' || c == '^') {
            // 연산자 앞에 숫자가 있었다면(current) 먼저 저장
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
            
            // 2-1. 단항 음수(Unary Minus) 처리:
            // 토큰이 비어있거나(맨 앞), 바로 앞 토큰이 여는 괄호이거나, 연산자일 때
            if (c == '-' && (tokens.empty() || tokens.back() == "(" || isOperator(tokens.back()))) {
                // '-'를 다음 숫자 토큰에 붙이기 위해 current에 추가
                current += c;
            } else {
                // 일반 연산자/괄호는 그 자체로 토큰
                tokens.push_back(std::string(1, c));
            }
        // 3. 숫자 (또는 음수의 일부)
        } else {
            current += c;
        }
    }
    
    // 마지막 토큰(current)이 남아있다면 저장
    if (!current.empty()) {
        tokens.push_back(current);
    }
    
    return tokens;
}

/**
 * @brief 중위 표기법 토큰 리스트를 후위 표기법(RPN)으로 변환합니다 (샤일링 야드 알고리즘).
 * @param tokens {"10", "+", "5", "*", "2"}
 * @return {"10", "5", "2", "*", "+"}
 */
std::vector<std::string> CalculatorService::infixToPostfix(const std::vector<std::string>& tokens) const{
    std::vector<std::string> output; // 후위 표기법 출력을 담을 벡터
    std::stack<std::string> operators; // 연산자와 괄호를 임시 저장할 스택
    
    for (const std::string& token : tokens) {
        // 1. 숫자 토큰: 바로 출력(output)으로 보냄
        if (isNumber(token)) {
            output.push_back(token);
        // 2. 여는 괄호 '(': 연산자 스택에 푸시
        } else if (token == "(") {
            operators.push(token);
        // 3. 닫는 괄호 ')':
        } else if (token == ")") {
            // 여는 괄호 '('가 나올 때까지 스택의 연산자를 모두 출력으로 보냄
            while (!operators.empty() && operators.top() != "(") {
                output.push_back(operators.top());
                operators.pop();
            }
            // 스택이 비었다면 괄호 짝이 안 맞는 것
            if (operators.empty()) {
                throw std::runtime_error("Mismatched parentheses");
            }
            operators.pop(); // '('를 스택에서 제거
        // 4. 연산자 토큰:
        } else if (isOperator(token)) {
            // 스택 top의 연산자 우선순위가 현재 토큰보다 높거나 같으면,
            // 스택의 연산자를 먼저 출력으로 보냄
            const bool isRightAssociative = (token == "^");
            while (!operators.empty() && operators.top() != "(" &&
                   (precedence(operators.top()) > precedence(token) ||
                    (precedence(operators.top()) == precedence(token) && !isRightAssociative))
                  ) 
            {
                output.push_back(operators.top());
                operators.pop();
            }
            // 현재 연산자를 스택에 푸시
            operators.push(token);
        } else {
            // 숫자도, 괄호도, 연산자도 아닌 경우 (예: 'x' 같은 변수)
            throw std::runtime_error("Invalid token: " + token);
        }
    }
    
    // 토큰 처리가 끝난 후, 스택에 남아있는 모든 연산자를 출력으로 보냄
    while (!operators.empty()) {
        if (operators.top() == "(" || operators.top() == ")") {
            // 괄호가 남아있으면 짝이 안 맞는 것
            throw std::runtime_error("Mismatched parentheses");
        }
        output.push_back(operators.top());
        operators.pop();
    }
    
    return output;
}

/**
 * @brief 후위 표기법(RPN) 토큰 리스트를 계산합니다.
 * @param postfix {"10", "5", "2", "*", "+"}
 * @return 계산 결과 (inf_int)
 */
inf_int CalculatorService::evaluatePostfix(const std::vector<std::string>& postfix) const{
    std::stack<inf_int> stack; // 피연산자(숫자)를 저장할 스택
    
    for (const std::string& token : postfix) {
        // 1. 숫자 토큰: 스택에 푸시 (문자열을 inf_int로 변환)
        if (isNumber(token)) {
            stack.push(inf_int(token.c_str()));
        // 2. 연산자 토큰:
        } else if (isOperator(token)) {
            // 연산자는 피연산자 2개가 필요함
            if (stack.size() < 2) {
                throw std::runtime_error("Invalid expression");
            }
            
            // 스택에서 피연산자 2개 꺼냄 (순서 중요: a 연산 b)
            inf_int b = stack.top(); stack.pop();
            inf_int a = stack.top(); stack.pop();
            
            // 연산 수행 (inf_int의 오버로딩된 연산자 사용)
            if (token == "+") {
                stack.push(a + b);
            } else if (token == "-") {
                stack.push(a - b);
            } else if (token == "*") {
                stack.push(a * b);
            } else if (token == "/") {
                stack.push(a / b);
            } else if (token == "^"){
                stack.push(a ^ b);
            }
            else {
                throw std::runtime_error("Unknown operator: " + token);
            }
        }
    }
    
    // 모든 계산이 끝나면 스택에는 최종 결과 하나만 남아있어야 함
    if (stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }
    
    // 최종 결과 반환
    return stack.top();
}

/**
 * @brief 연산자 우선순위를 반환합니다. (숫자가 클수록 높음)
 */
int CalculatorService::precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0; // 괄호 등 기타
}

/**
 * @brief 토큰이 지원하는 연산자인지 확인합니다.
 */
bool CalculatorService::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

/**
 * @brief 토큰이 숫자인지 확인합니다. (음수 부호 포함)
 * 예: "123" (true), "-123" (true), "-" (false), "1a2" (false)
 */
bool CalculatorService::isNumber(const std::string& token) {
    if (token.empty()) return false;
    
    size_t start = 0;
    // 1. 토큰이 '-'로 시작하는 경우 (음수 가능성)
    if (token[0] == '-') {
        start = 1; // 두 번째 문자부터 숫자 검사 시작
        // 토큰이 "-" 하나로만 이루어져 있다면 숫자가 아님 (연산자임)
        if (token.length() == 1) return false;
    }
    
    // 2. 나머지 문자열이 모두 숫자인지 확인
    for (size_t i = start; i < token.length(); i++) {
        if (!std::isdigit(token[i])) {
            return false;
        }
    }
    
    return true;
}