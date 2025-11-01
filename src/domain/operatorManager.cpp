#include "operatorManager.h"
#include <stdexcept>

OperatorManager::OperatorManager() {
   opers.push_back({"+", 3});
   opers.push_back({"-", 3});
   opers.push_back({"*", 1});
   opers.push_back({"/", 1});
   opers.push_back({"^", 1});
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


// operator 존재 확인
bool OperatorManager::isOperator(string str) const {
   for (const auto& op : opers) {
      if (op.expr == str) return true;
   }
   return false;
}

// execute 함수
inf_int OperatorManager::execute(string opStr, inf_int a, inf_int b) const {
   for (const auto& op : opers) {
      if (op.expr == opStr) {
         // const 메서드에서는 멤버 함수 포인터를 직접 호출할 수 없으므로 직접 구현
         if (opStr == "+") return add(a, b);
         else if (opStr == "-") return sub(a, b);
         else if (opStr == "*") return mul(a, b);
         else if (opStr == "/") return div(a, b);
         else if (opStr == "^") return pow(a, b);
      }
   }
   throw runtime_error("Unknown operator: " + opStr);
}

