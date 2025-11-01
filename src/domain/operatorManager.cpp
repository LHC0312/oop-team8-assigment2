#include "operatorManager.h"
#include <stdexcept>

OperatorManager::OperatorManager() {
   opers.push_back({"=", 0, OperatorType::ASSIGN});
   opers.push_back({"+", 1, OperatorType::ADD});
   opers.push_back({"-", 1, OperatorType::SUB});
   opers.push_back({"*", 2, OperatorType::MUL});
   opers.push_back({"/", 2, OperatorType::DIV});
   opers.push_back({"^", 3, OperatorType::POW});
}

// 연산 함수
inf_int OperatorManager::add(inf_int a, inf_int b) const {
  return a + b;
}

inf_int OperatorManager::sub(inf_int a, inf_int b) const {
   return a - b;
}

inf_int OperatorManager::mul(inf_int a, inf_int b) const {
  return a * b;
}

inf_int OperatorManager::div(inf_int a, inf_int b) const {
   return a / b;
}

inf_int OperatorManager::pow(inf_int a, inf_int b) const {
   return a ^ b;
}

inf_int OperatorManager::assign(inf_int a, inf_int b) const {
   return b;
}


// operator 존재 확인
bool OperatorManager::isOperator(string str) const {
   for (const auto& op : opers) {
      if (op.expr == str) return true;
   }
   return false;
}

// operator 우선순위 반환
int OperatorManager::getPrecedence(string str) const {
   for (const auto& op : opers) {
      if (op.expr == str) return op.priority;
   }
   return 0; // 없는 연산자는 우선순위 0
}

inf_int OperatorManager::execute(string opStr, inf_int a, inf_int b) const {
   for (const auto& op : opers) {
      if (op.expr == opStr) {
         switch (op.type) {
            case OperatorType::ADD:
               return add(a, b);
            case OperatorType::SUB:
               return sub(a, b);
            case OperatorType::MUL:
               return mul(a, b);
            case OperatorType::DIV:
               return div(a, b);
            case OperatorType::POW:
               return pow(a, b);
            case OperatorType::ASSIGN:
               return assign(a, b);
         }
      }
   }
   throw std::runtime_error("Unknown operator: " + opStr);
}



