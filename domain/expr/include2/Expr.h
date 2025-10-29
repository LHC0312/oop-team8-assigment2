#pragma once
#include <string>
#include "../../include/inf_int.h"

class Expr {
public:
    virtual ~Expr() {}
};

// 끝. 다른 거 넣지 마.
// 특히 virtual inf_int evaluate(...) 같은 거 절대 넣지 마.
