#ifndef VARIABLE_H
#define VARIABLE_H


#include "variable.h"
#include "inf_int.h"
#include <string>
#include <vector>
using namespace std;

class Variable {
  private:
  const vector<string> exprs = {"X", "x"};
  public:
  bool isVariable(string s);
  inf_int substitute(inf_int k);
};

#endif //VARIABLE_H
