#ifndef OPERATORMANAGER_H
#define OPERATORMANAGER_H

#include "inf_int.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class OperatorManager;

struct Operator {
   string expr;
   int priority;
};

class OperatorManager {
   private:
      vector<Operator> opers;

      inf_int add(inf_int a, inf_int b) const;
      inf_int sub(inf_int a, inf_int b) const;
      inf_int mul(inf_int a, inf_int b) const;
      inf_int div(inf_int a, inf_int b) const;
      inf_int pow(inf_int a, inf_int b) const;

   public:
      OperatorManager();
      bool isOperator(string str) const;
      inf_int execute(string opStr, inf_int a, inf_int b) const;
};

#endif // OPERATORMANAGER_H