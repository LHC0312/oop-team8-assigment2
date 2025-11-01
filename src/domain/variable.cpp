//
// Created by 이해찬 on 2025. 10. 30..
//
#include "variable.h"

bool Variable::isVariable(string s) const {
  for (const string& expr : exprs) {
    if (expr  == s) return true;
  }
  return false;
}

inf_int Variable::substitute(inf_int k) const {
  return k;
}
