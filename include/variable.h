#ifndef VARIABLE_H
#define VARIABLE_H


#include "inf_int.h"
#include <string>
#include <vector>
using namespace std;

class Variable {
  private:
  const vector<string> exprs = {"X", "x"};
  public:
  bool isVariable(string s) const;
  inf_int substitute(inf_int k) const;
};

#endif //VARIABLE_H
