#include "operatorManager.h"

OperatorManager::OperatorManager() {
   opers.push_back({"+", 3, &OperatorManager::add});
   opers.push_back({"-", 3, &OperatorManager::sub});
   opers.push_back({"*", 1, &OperatorManager::mul});
   opers.push_back({"/", 1, &OperatorManager::div});
   opers.push_back({"^", 1, &OperatorManager::pow});
}

// 연산 함수
inf_int OperatorManager::add(inf_int a, inf_int b) {
  return a + b;
}

inf_int OperatorManager::sub(inf_int a, inf_int b) {
   return a - b;
}

inf_int OperatorManager::mul(inf_int a, inf_int b) {
  return a * b;
}

inf_int OperatorManager::div(inf_int a, inf_int b) {
   return a / b;
}

inf_int OperatorManager::pow(inf_int a, inf_int b) {
   inf_int result = 1;
   for (int i=0; i<b; i++) a = a * a;
   return result;
}


// operator 존재 확인
bool OperatorManager::isOperator(string str) {
   for (auto& op : opers) {
      if (op.expr == str) return true;
   }
   return false;
}

// execute 함수
//inf_int OperatorManager::execute(string opStr, inf_int a, inf_int b) {
//   for (auto& op : opers) {
//      if (op.expr == opStr) {
//         return (this->*op.function)(a, b); // 멤버 함수 포인터 호출
//      }
//   }
//   throw runtime_error("Unknown operator: " + opStr);
//}

