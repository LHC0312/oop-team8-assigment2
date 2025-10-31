#include "inf_int.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class OperatorManager;

struct Operator {
   string expr;
   int priority;
   inf_int (OperatorManager::*function)(inf_int, inf_int);
};

class OperatorManager {
   private:
      vector<Operator> opers;

      inf_int add(inf_int a, inf_int b);
      inf_int sub(inf_int a, inf_int b);
      inf_int mul(inf_int a, inf_int b);
      inf_int div(inf_int a, inf_int b);
      inf_int pow(inf_int a, inf_int b);

   public:
      OperatorManager();
      bool isOperator(string str);
      inf_int execute(string opStr, inf_int a, inf_int b);
};